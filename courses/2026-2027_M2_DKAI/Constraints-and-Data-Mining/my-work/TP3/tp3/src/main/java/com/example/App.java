package com.example;

import org.chocosolver.mining.patterns.constraints.factory.ConstraintFactory;
import org.chocosolver.mining.patterns.io.TransactionFiles;
import org.chocosolver.mining.patterns.io.TransactionalDatabase;
import org.chocosolver.mining.patterns.search.strategy.selectors.variables.MinCov;
import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.search.strategy.Search;
import org.chocosolver.solver.search.strategy.selectors.values.IntDomainMin;
import org.chocosolver.solver.variables.BoolVar;
import org.chocosolver.solver.variables.IntVar;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) throws Exception {
        //System.out.println("Hello World!");

        test("/home/user/cours/DKAI/CP/TP3/chocominer/chocominer-core/src/test/resources/contextPasquier99/contextPasquier99.dat", "contextPasquier99.dat");
        System.out.println("--------------------------------------------------");
        test("/home/user/cours/DKAI/CP/TP3/chocominer/datasets/itemset/lazaar.txt", "lazaar.txt");
        System.out.println("------------------------------------------------------");
        testQ4("/home/user/cours/DKAI/CP/TP3/chocominer/datasets/itemset/lazaar.txt", "lazaar.txt", 3, 2);
    }

    //E2, Question 2
    private static void test(String file, String testname) throws Exception {
        TransactionalDatabase lazaar = TransactionFiles.readItems(file);
        Model model = new Model("Closed Itemset Mining");
        BoolVar[] x = model.boolVarArray("x", lazaar.getNbItems());
        
        //E2, Question 3.1
        double minRelativeFrequency = 0.2;
        int minFreq = (int) Math.ceil(minRelativeFrequency * lazaar.getNbTransactions());
        
        IntVar freq = model.intVar("freq", minFreq, lazaar.getNbTransactions());
        IntVar length = model.intVar("length", 1, lazaar.getNbItems());
        model.sum(x, "=", length).post();
        ConstraintFactory.coverSize(lazaar, freq, x).post();
        ConstraintFactory.coverClosure(lazaar, x).post();

        //E2, Question 3.2
        int minLength = 3;
        model.arithm(length, ">=", minLength).post();

        Solver solver = model.getSolver();

        solver.setSearch(Search.intVarSearch(new MinCov(model, lazaar), new IntDomainMin(), x));

        int nbSol = 0;
        long time = System.currentTimeMillis();
        while (solver.solve()) {
            nbSol++;
            System.out.print("Solution " + nbSol + ": ");
            for (int i = 0; i < x.length; i++) {
                if (x[i].getValue() == 1) {
                    System.out.print(i + " "); 
                }
            }
        }
        time = System.currentTimeMillis() - time;
        System.out.println("Database: " + testname);
        System.out.println("Time: " + time+"ms");
        System.out.println("Number of solutions: " + nbSol);
    }

    //E2, Question 4
    private static void testQ4(String file, String testname, int catSize, int m) throws Exception {
        TransactionalDatabase db = TransactionFiles.readItems(file);
        Model model = new Model("Closed Itemset Mining");
        BoolVar[] x = model.boolVarArray("x", db.getNbItems());
        IntVar freq = model.intVar("freq", 1, db.getNbTransactions());
        IntVar length = model.intVar("length", 1, db.getNbItems());
        model.sum(x, "=", length).post();
        ConstraintFactory.coverSize(db, freq, x).post();
        ConstraintFactory.coverClosure(db, x).post();

        //which category x_i is belonging to
        int n = db.getNbItems();
        int nbCat = n / catSize;
        //items without categories are in the last cat

        BoolVar[][] catVars = new BoolVar[nbCat][];
        for(int i = 0; i < n; i++){
            if( i >= nbCat*catSize){
                break;
            }
            int cat = i / catSize;
            if (catVars[cat] == null) {
                catVars[cat] = new BoolVar[catSize];
            }
            catVars[cat][i - cat * catSize] = x[i];
        }

        IntVar distinctCat = model.intVar("distinctCat", 1, nbCat);
        BoolVar[] usedVars = new BoolVar[nbCat];
        for (int c = 0; c < nbCat; c++) {
            BoolVar used = model.boolVar("used_" + c);
            model.sum(catVars[c], ">=", 1).reifyWith(used);
            usedVars[c] = used;
        }
        model.sum(usedVars, "=", distinctCat).post();
        model.arithm(distinctCat, ">=", m).post();
        
        Solver solver = model.getSolver();
        solver.setSearch(Search.intVarSearch(new MinCov(model, db), new IntDomainMin(), x));

        int nbSol = 0;
        long time = System.currentTimeMillis();
        while (solver.solve()) {
            nbSol++;
            System.out.print("Solution " + nbSol + ": ");
            for (int i = 0; i < x.length; i++) {
                if (x[i].getValue() == 1) {
                    System.out.print(i + " ");
                }
            }
            System.out.print("; Freq : " + freq.getValue());
            System.out.println();
        }
        time = System.currentTimeMillis() - time;
        System.out.println("Time: " + time + "ms");
        System.out.println("Number of solutions: " + nbSol);
        System.out.println("Database: " + testname);

        
    }
}
