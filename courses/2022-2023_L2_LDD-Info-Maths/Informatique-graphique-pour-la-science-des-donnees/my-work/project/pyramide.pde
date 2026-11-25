



PShape rectangle3D(float l1, float l2, float h, float posH, float posW, int size){
    PShape rect = createShape();
    rect.translate(posW, posW, posH);
    
    rect.beginShape(QUADS);
    rect.noStroke();
    textureWrap(REPEAT);
    rect.texture(stones);
    // rect.tint(240, 240, 10);

    rect.vertex(0, 0, 0, 0, 0);
    rect.vertex(l1, 0, 0, size, 0);
    rect.vertex(l1, 0, h, size, 1);
    rect.vertex(0, 0, h, 0, 1);

    rect.vertex(0, 0, 0, 0, 0);
    rect.vertex(0, l2, 0, size, 0);
    rect.vertex(0, l2, h, size, 1);
    rect.vertex(0, 0, h, 0, 1);

    // rect.fill(255,0, 255);
    rect.vertex(0, l2, 0, 0, 0);
    rect.vertex(l1, l2, 0, size, 0);
    rect.vertex(l1, l2, h, size, 1);
    rect.vertex(0, l2, h, 0, 1);

    // rect.fill(0,0,255);
    rect.vertex(l1, 0, 0, 0, 0);
    rect.vertex(l1, l2, 0, size, 0);
    rect.vertex(l1, l2, h, size, 1);
    rect.vertex(l1, 0, h,  0, 1);
    rect.endShape();
    return rect;
}

PShape dessusMarche(float l1, float gl1, float l2, float gl2, float posH, float posW, int size){
    float r = (l1 - l2)/2.0;
    float gr = (gl1 - gl2)/2.0;
    
    PShape dessus = createShape();
    dessus.translate(posW, posW, posH);
    
    dessus.beginShape(QUADS);
    dessus.noStroke();
    textureWrap(REPEAT);
    dessus.texture(stones);
    // dessus.tint(240, 240, 10);

    dessus.vertex(0, 0, 0, 0, 0);
    dessus.vertex(l2+r, 0, 0, size, 0);
    dessus.vertex(l2+r, gr, 0, size, 1);
    dessus.vertex(0, gr, 0, 0, 1);

    // dessus.fill(255,255,0);
    dessus.vertex(0, gr, 0, 0, 0);
    dessus.vertex(0, gl1, 0, size, 0);
    dessus.vertex(r, gl1, 0, size, 1);
    dessus.vertex(r, gr, 0, 0, 1);

    // dessus.fill(255,0, 255);
    dessus.vertex(r, gl1, 0, 0, 0);
    dessus.vertex(l1, gl1, 0, size, 0);
    dessus.vertex(l1, gl2+gr, 0, size, 1);
    dessus.vertex(r, gl2+gr, 0, 0, 1);

    // dessus.fill(0,0,255);
    dessus.vertex(l1, 0, 0, 0, 0);
    dessus.vertex(l1, gl2+gr, 0, size, 0);
    dessus.vertex(l2+r, gl2+gr, 0, size, 1);
    dessus.vertex(l1-r, 0, 0, 0, 1);

    dessus.endShape();
    return dessus;
}

PShape rectangle3DAvecPorte(float l1, float l2, float h, float posH, float posW, int size, float posPorte, float porteWidth){
    PShape rect = createShape();
    rect.translate(posW, posW, posH);

    rect.beginShape(QUADS);
    rect.noStroke();
    textureWrap(REPEAT);
    rect.texture(stones);
    // rect.tint(240, 240, 10);

    rect.vertex(0, 0, 0, 0, 0);
    rect.vertex(posPorte, 0, 0, size, 0);
    rect.vertex(posPorte, 0, h, size, 1);
    rect.vertex(0, 0, h, 0, 1);

    rect.vertex(posPorte+porteWidth, 0, 0, 0, 0);
    rect.vertex(l1, 0, 0, size, 0);
    rect.vertex(l1, 0, h, size, 1);
    rect.vertex(posPorte+porteWidth, 0, h, 0, 1);

    rect.vertex(0, 0, 0, 0, 0);
    rect.vertex(0, l2, 0, size, 0);
    rect.vertex(0, l2, h, size, 1);
    rect.vertex(0, 0, h, 0, 1);

    // rect.fill(255,0, 255);
    rect.vertex(0, l2, 0, 0, 0);
    rect.vertex(l1, l2, 0, size, 0);
    rect.vertex(l1, l2, h, size, 1);
    rect.vertex(0, l2, h, 0, 1);

    // rect.fill(0,0,255);
    rect.vertex(l1, 0, 0, 0, 0);
    rect.vertex(l1, l2, 0, size, 0);
    rect.vertex(l1, l2, h, size, 1);
    rect.vertex(l1, 0, h,  0, 1);
    rect.endShape();
    return rect;
}

PShape dessusMarcheAvecPorte(float l1, float gl1, float l2, float gl2, float posH, float posW, int size, float posPorte, float porteWidth){
    float r = (l1 - l2)/2.0;
    float gr = (gl1 - gl2)/2.0;
    
    PShape dessus = createShape();
    dessus.translate(posW, posW, posH);
    
    dessus.beginShape(QUADS);
    dessus.noStroke();
    textureWrap(REPEAT);
    dessus.texture(stones);
    // dessus.tint(240, 240, 10);

    dessus.vertex(0, 0, 0, 0, 0);
    dessus.vertex(posPorte, 0, 0, size, 0);
    dessus.vertex(posPorte, gr, 0, size, 1);
    dessus.vertex(0, gr, 0, 0, 1);

    dessus.vertex(posPorte+porteWidth, 0, 0, 0, 0);
    dessus.vertex(l1, 0, 0, size, 0);
    dessus.vertex(l1, gr, 0, size, 1);
    dessus.vertex(posPorte+porteWidth, gr, 0, 0, 1);

    // dessus.fill(255,255,0);
    dessus.vertex(0, gr, 0, 0, 0);
    dessus.vertex(0, gl1, 0, size, 0);
    dessus.vertex(r, gl1, 0, size, 1);
    dessus.vertex(r, gr, 0, 0, 1);

    // dessus.fill(255,0, 255);
    dessus.vertex(r, gl1, 0, 0, 0);
    dessus.vertex(l1, gl1, 0, size, 0);
    dessus.vertex(l1, gl2+gr, 0, size, 1);
    dessus.vertex(r, gl2+gr, 0, 0, 1);

    // dessus.fill(0,0,255);
    dessus.vertex(l1, gr, 0, 0, 0);
    dessus.vertex(l1, gl2+gr, 0, size, 0);
    dessus.vertex(l2+r, gl2+gr, 0, size, 1);
    dessus.vertex(l1-r, gr, 0, 0, 1);

    dessus.endShape();
    return dessus;
}
PShape pointe(float l1, float l2, float h, float posH, float posW){
    PShape pointe = createShape();
    PImage tex = loadImage("src/pointe.jpg");
    pointe.translate(posW, posW, posH);
    pointe.beginShape(TRIANGLE_FAN);
    pointe.noStroke();
    
    pointe.texture(tex);

    pointe.vertex(l1/2, l2/2, h);

    pointe.vertex(0, 0, 0, 0, 0);
    pointe.vertex(l1, 0, 0, 0, 1);
    pointe.vertex(l1, l2, 0, 1, 1);
    pointe.vertex(0, l2, 0, 1, 0);
    pointe.vertex(0, 0, 0, 0, 0);

    pointe.endShape();
    return pointe;
}

public class Pyramide{
    int size;
    int nbEtage;
    int nbMarche;
    
    public Pyramide(int s, int etage, int marche){
        this.size = s+4;
        this.nbEtage = etage;
        this.nbMarche = marche;
    }
    public Pyramide(int s, int etage){this(s, etage, 30);}

    public PShape generate(){
        PShape pyramide = createShape(GROUP);
        
        float heightMarche = 100.0/nbMarche;
        float widthMarche = size*50;
        float depthMarche = 100.0/nbMarche/2.0;
        // pushMatrix();
        // push();
        // tint(240, 240, 10);
        float posPorte = 100;
        float porteWidth = 50;
        
        for(int etage = 0; etage < nbEtage; etage++){
            if(etage == 1){
                for(int marche = 0; marche < nbMarche; marche++){
                    pyramide.addChild(rectangle3DAvecPorte(widthMarche, widthMarche, heightMarche, heightMarche*(marche+etage*nbMarche), depthMarche*(marche+nbMarche*etage), size/3, posPorte, porteWidth));
                    pyramide.addChild(dessusMarcheAvecPorte(widthMarche, widthMarche, widthMarche-depthMarche*2, widthMarche-depthMarche*2, heightMarche*(marche+1+etage*nbMarche), depthMarche*(marche+nbMarche*etage), size/3, posPorte, porteWidth));
                    widthMarche -= depthMarche*2;
                    posPorte -= depthMarche;
                }
            }
            else{
                for(int marche = 0; marche < nbMarche; marche++){
                    
                    pyramide.addChild(rectangle3D(widthMarche, widthMarche, heightMarche, heightMarche*(marche+etage*nbMarche), depthMarche*(marche+nbMarche*etage), size/3));
                    pyramide.addChild(dessusMarche(widthMarche, widthMarche, widthMarche-depthMarche*2, widthMarche-depthMarche*2, heightMarche*(marche+1+etage*nbMarche), depthMarche*(marche+nbMarche*etage), size/3));
                    widthMarche -= depthMarche*2;
                }
            }
        }
        // pop();
        // popMatrix();
        float a = heightMarche*(nbEtage*nbMarche);
        float b = depthMarche*(nbEtage*nbMarche);

        float c = sqrt(pow(a, 2) + pow(b, 2));
        float wn = widthMarche;
        float w0 = size*50.0;

        float x = wn/w0*c*(1/(1-(wn/w0)));
        // println("x = "+x);
        pyramide.addChild(pointe(widthMarche, widthMarche, x, heightMarche*(nbMarche*nbEtage), depthMarche*(nbMarche*nbEtage)));



    return pyramide;
    }
}

