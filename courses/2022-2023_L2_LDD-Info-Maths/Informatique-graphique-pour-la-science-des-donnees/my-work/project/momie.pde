public class Momie {
    public PVector position;
    public PVector oldPos;
    public PVector mvtDir = new PVector(0,0);

    public int grosseur;
    public int hauteur;
    public PShape pshape;
    public float angleZ = 0;

    public Momie(PVector pos, int g, int h){
        this.position = pos.copy();
        this.oldPos = pos.copy();
        this.grosseur = g;
        this.hauteur = h;
        this.pshape = this.createCorps(g, h);
    }
    private float circleCurve(float x){
        return sqrt(1 - pow(x, 2));
    }
    public PShape createBoudin(float grosseur, float hauteur){
        /**
        1 tour de ruban par cran de hauteur
         */
        PShape shape = createShape();
        shape.beginShape(QUADS);
        shape.ambient(255,255,255);
        shape.specular(0);
        shape.shininess(0);
        shape.fill(255, 255, 255);
        shape.noStroke();
        for(float currentH = 0; currentH < hauteur; currentH++){
            //un tour de ruban
            for(float angle = 0; angle <= 360; angle++){
                float croissance = map(angle, 0, 360, 0, 1);
                float croissancep1 = map(angle+1, 0, 360, 0, 1);

                //on veut que quand croissance = 1, 
                float radius = grosseur*this.circleCurve(map(currentH+croissance, 0, hauteur, -1, 1)) + (1/2.)*grosseur*noise( (grosseur/2.)*(croissance + currentH));
                float radiusp1 = grosseur*this.circleCurve(map(currentH+croissancep1, 0, hauteur, -1, 1)) + (1/2.)*grosseur*noise( (grosseur/2.)*(croissancep1 + currentH));

                float x = cos(radians(angle));
                float y = sin(radians(angle));
                float xp1 = cos(radians(angle+1));
                float yp1 = sin(radians(angle+1));

                shape.vertex(x*radius, y*radius, currentH+croissance);
                shape.vertex(x*radius, y*radius, currentH+1+croissance);
                shape.vertex(xp1*radiusp1, yp1*radiusp1, currentH+1+croissance);
                shape.vertex(xp1*radiusp1, yp1*radiusp1, currentH+croissance);
            }
        }
        shape.endShape(CLOSE);
        return shape;
    }
    public PShape createBras(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);     //composé de 2 shape de laby
        PShape boudin = createBoudin(grosseur/4, hauteur);
        PShape main1 = this.createMain();
        boudin.translate(0, 0, -hauteur);
        main1.scale(3);
        main1.translate(0, 0, -3-hauteur);
        shape0.addChild(main1);
        shape0.addChild(boudin);

        return shape0;  
    }
     public PShape createBras2(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);     //composé de 2 shape de laby
        PShape boudin = createBoudin(grosseur/4, hauteur);
        PShape main1 = this.createMain2();
        boudin.translate(0, 0, -hauteur);
        main1.scale(3);
        main1.translate(0, 0, -3-hauteur);
        shape0.addChild(main1);
        shape0.addChild(boudin);

        return shape0;  
    }
    public PShape createJambe(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);     //composé de 2 shape de laby
        PShape boudin = createBoudin(grosseur/4, hauteur + (2/3)*hauteur);
        PShape pied1 = this.createPied();
        pied1.translate(4, 0, -hauteur+(1/3)*hauteur);
        boudin.translate(0, 0, -hauteur + (1/3)*hauteur);
        shape0.addChild(pied1);
        shape0.addChild(boudin);

        return shape0;
    }
    public PShape createMain(){
        PShape shape0;
        if(lowPolyHand){
            shape0 = createBoudin(10,20);
            shape0.scale(0.1,0.1,0.1);
        }else{
            shape0 = loadShape("src/hand.obj");
            shape0.scale(0.3,0.3,0.3);
            shape0.rotateZ(PI);
            shape0.rotateY(PI);
            shape0.translate(-1 ,1, 2);
        }
        
        return shape0;
    }
    public PShape createMain2(){
        PShape shape0;
        if(lowPolyHand){
            shape0 = createBoudin(10,20);
            shape0.scale(0.1,0.1,0.1);
        }else{
            shape0 = loadShape("src/hand1.obj");
            shape0.scale(0.3,0.3,0.3);
            shape0.rotateZ(PI);
            shape0.rotateY(PI);
            shape0.translate(1 ,1, 2);
        }
       return shape0;
    }
    public PShape createPied(){
        PShape shape0 = createBoudin(20,10);
        shape0.scale(0.3, 0.1, 0.2);
        return shape0;
    }
    public PShape createPupille(){
        PShape shape0 = createSphere(color(0,0,0));
        shape0.scale(0.05, 0.05, 0.05);
        return shape0;
    }
    public PShape createBlancDesYeux(){
        PShape shape0 = createSphere(color(255,255,255));
        shape0.scale(0.05, 0.2, 0.1);
        
        return shape0;
    }
    
    public PShape createOeil(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);
        PShape blanc = this.createBlancDesYeux();
        PShape pupille = this.createPupille();
        pupille.translate(0.5, 0, 0);
        shape0.addChild(blanc);
        shape0.addChild(pupille);
        shape0.scale(1, grosseur/10, hauteur/20);
        return shape0;
    }
    public PShape createTete(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);
        PShape oeil1 = this.createOeil(grosseur, hauteur);
        PShape oeil2 = this.createOeil(grosseur, hauteur);
        PShape boudin = this.createBoudin(grosseur, hauteur);
        oeil2.translate(0, grosseur/5, 0);
        oeil1.translate(0, -grosseur/5, 0);
        oeil1.scale(1.1,1.1,1.1);
        oeil2.scale(1.1,1.1,1.1);

        boudin.scale(0.5, 0.5, 0.5);
        boudin.translate(-grosseur+2, 0, -hauteur/4.);
        shape0.addChild(oeil1);
        shape0.addChild(oeil2);
        shape0.addChild(boudin);
        return shape0;
    }
    public PShape createBuste(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);
        PShape boudin = this.createBoudin(grosseur/2., hauteur/2.);
        boudin.scale(0.3, 0.5, 1*1.33);
        boudin.scale(2);
        boudin.translate(-grosseur+2, 0, -hauteur/4.);
        shape0.addChild(boudin);
        return shape0;
    }
    public PShape createCorps(float grosseur, float hauteur){
        PShape shape0 = createShape(GROUP);
        PShape buste = this.createBuste(grosseur, hauteur);
        PShape tete = this.createTete(grosseur, hauteur);
        PShape bras1 = this.createBras2(grosseur, hauteur);
        PShape bras2 = this.createBras(grosseur, hauteur);
        PShape jambe1 = this.createJambe(grosseur, hauteur);
        PShape jambe2 = this.createJambe(grosseur, hauteur);
        tete.translate(0, 0, hauteur*1.33);
        bras1.rotateX(radians(90));
        bras1.rotateY(radians(180));
        bras1.rotateZ(-radians(90));
        bras1.translate(-grosseur, grosseur/2.,hauteur);
        bras2.rotateX(-radians(90));
        bras2.rotateZ(radians(90));
        bras2.translate(-grosseur, -grosseur/2., hauteur);
        jambe1.translate(-grosseur/1.33, -grosseur/2.5, 0);
        jambe2.translate(-grosseur/1.33, grosseur/2.5, 0);
        shape0.addChild(buste);
        shape0.addChild(tete);
        shape0.addChild(bras1);
        shape0.addChild(bras2);
        shape0.addChild(jambe1);
        shape0.addChild(jambe2);
        shape0.translate(0,0,-hauteur/3. + 2);
        return shape0;
    }
}