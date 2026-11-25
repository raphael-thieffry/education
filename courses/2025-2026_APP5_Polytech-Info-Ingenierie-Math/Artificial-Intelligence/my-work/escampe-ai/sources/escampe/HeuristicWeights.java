package escampe;

import java.io.*;
import java.util.Locale;

/**
 * Vecteur de poids pour l'heuristique paramétrisée (H_PARAM dans EscampeHeuristics).
 * Les valeurs par défaut sont les constantes hardcodées de H_V2.
 */
public class HeuristicWeights implements Cloneable {

    public double proximity;    // (10 - minBfsToOppLic) * proximity
    public double safety;       // minBfsToMyLic * safety
    public double killShot;     // killShot * killShot
    public double danger;       // dangerCount * danger
    public double immThreat;    // -immediateThreat * immThreat
    public double threat;       // -threatCount * threat
    public double licMobility;  // licMobility * licMobility
    public double myLisere;     // myLisereCoverage * myLisere
    public double oppLisere;    // -oppLisereCoverage * oppLisere
    public double mobility;     // (myMoves - oppMoves) * mobility

    /** Valeurs par défaut = constantes H_V2. */
    public static HeuristicWeights defaults() {
        HeuristicWeights w = new HeuristicWeights();
        w.proximity   = 20.154210;
        w.safety      = 10.000000;
        w.killShot    = 23.102567;
        w.danger      = 15.000000;
        w.immThreat   = 50.000000;
        w.threat      = 25.000000;
        w.licMobility = 12.000000;
        w.myLisere    = 20.000000;
        w.oppLisere   = 10.166130;
        w.mobility    =  4.544243;
        return w;
    }

    @Override
    public HeuristicWeights clone() {
        try { return (HeuristicWeights) super.clone(); }
        catch (CloneNotSupportedException e) { throw new AssertionError(); }
    }

    public double[] toArray() {
        return new double[]{proximity, safety, killShot, danger, immThreat,
                            threat, licMobility, myLisere, oppLisere, mobility};
    }

    public void fromArray(double[] a) {
        proximity   = a[0]; safety      = a[1]; killShot    = a[2];
        danger      = a[3]; immThreat   = a[4]; threat      = a[5];
        licMobility = a[6]; myLisere    = a[7]; oppLisere   = a[8];
        mobility    = a[9];
    }

    /** Sauvegarde dans un fichier texte (un poids par ligne). */
    public void save(String path) throws IOException {
        try (PrintWriter pw = new PrintWriter(new FileWriter(path))) {
            for (double v : toArray()) pw.printf(Locale.US, "%.6f%n", v);
        }
    }

    /** Charge depuis un fichier texte produit par save(). */
    public static HeuristicWeights load(String path) throws IOException {
        double[] a = new double[10];
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            for (int i = 0; i < 10; i++) a[i] = Double.parseDouble(br.readLine().trim());
        }
        HeuristicWeights w = new HeuristicWeights();
        w.fromArray(a);
        return w;
    }

    @Override
    public String toString() {
        return String.format(Locale.US,
            "[prox=%.1f safe=%.1f kill=%.1f danger=%.1f immThr=%.1f " +
            "thr=%.1f licMob=%.1f myLis=%.1f oppLis=%.1f mob=%.1f]",
            proximity, safety, killShot, danger, immThreat,
            threat, licMobility, myLisere, oppLisere, mobility);
    }
}
