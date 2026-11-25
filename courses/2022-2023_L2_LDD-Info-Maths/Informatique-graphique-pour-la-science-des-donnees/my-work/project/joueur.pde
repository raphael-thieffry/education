class Joueur{
    float angleX = 0;
    float angleY = PI;
    float angleZ = PI/2;
    
    float oldAngleZ = angleZ;
    float mvtAngleZ = 0;

    float x = 25 + 50;
    float y = 25;
    float z = 25;

    PVector oldPos = new PVector(x, y, z);//coordonnées de la camera
    PVector pos = new PVector(x, y, z);   //coordonnées du personnage
    PVector mvtDir = new PVector(0,0,0);

    int cpt = 0;
    int cptAngle = 0;
    int cptMaxVal = 10;
    int petitPas = 2;

    //nouveautées

    ArrayList<PVector> chemin = new ArrayList<PVector>();

    Joueur(){
    }

    void animateMarche(){
        if(cpt != 0){             
            // println("anim"+cpt + " pos : " +pos + " oldPos : " + oldPos);                             //animation handler
            cpt--;
            if((mvtDir.x == 0 && mvtDir.y == 0 && mvtDir.z == 0) || (cpt == cptMaxVal)){  //tentative de desac anim de marche quand change de niveau
                mvtDir = PVector.sub(pos, oldPos);
                mvtDir = mvtDir.div(float(cptMaxVal));                    //define one animation step
            }
            oldPos.add(mvtDir);                                  //add animation step
            oldPos.z = oldPos.z+sin((float(cpt)/cptMaxVal)*petitPas*PI);   //camera wobble
        }else{                                                 //end animation
            mvtDir = new PVector(0,0,0);
            oldPos = pos.copy();
            if(chemin.size() > 0){ //si morceau terminé mais chemin pas fini

                // println("IL RESTE " + chemin.size() + " MORCEAUX AVANT D'ARRIVER");
                pos = chemin.get(0);
                chemin.remove(0);
                cpt = cptMaxVal;
            }
        }
    }

    void animateAngle(){
        if(cptAngle != 0){             
            cptAngle--;
            if(mvtAngleZ == 0 || (cptAngle == cptMaxVal)){
                mvtAngleZ = (angleZ - oldAngleZ)/float(cptMaxVal); //define one animation step
            }
            oldAngleZ += mvtAngleZ;                                  //add animation step
        }else{                                                 //end animation
            mvtAngleZ = 0;
            oldAngleZ = angleZ;
        }
    }
    void setPosAnime(PVector pos){
        this.pos = pos;
        cpt = cptMaxVal;
    }
    void setAngleAnime(float angle){
        angleZ = angle;
        cptAngle = cptMaxVal;
    }
    void setPosTeleporte(PVector pos){
        this.pos = pos;
        oldPos = pos.copy();
    }
    boolean cheminEnCours(){
        return chemin.size() > 0;
    }   
    void setChemin(ArrayList<PVector> chemin){
        this.chemin = chemin;
    }
    void addVectorToChemin(PVector vec){
        if(chemin.size() == 0){
            chemin.add(this.pos.add(vec.copy()).copy());
        }else{
            chemin.add(chemin.get(chemin.size()-1).add(vec.copy()).copy());
        }
    }
    PVector setEstFaceAImpasseDirAndRetPos(Direction dir){
        if(!dansLaby){
            estFaceAImpasse = false;
            return new PVector(coordX, coordY);
        }else{
            int[][][] listeImpasses = laby.sides;
            int explorateurX = coordX;
            int explorateurY = coordY;
            while(
                explorateurX < laby.LAB_SIZE && explorateurY < laby.LAB_SIZE 
                && explorateurX >= 0         && explorateurY >= 0
                && listeImpasses[explorateurX][explorateurY][0] == 0
                && listeImpasses[explorateurX][explorateurY][1] == 0
                && listeImpasses[explorateurX][explorateurY][2] == 0
                && listeImpasses[explorateurX][explorateurY][3] == 0 
                ){
                /* println("explorateurX : " + explorateurX + " explorateurY : " + explorateurY);
                println(
                    "Impasses 0 : "
                 + listeImpasses[explorateurX][explorateurY][0] 
                 + " Impasses 1 : "
                 + listeImpasses[explorateurX][explorateurY][1] 
                 + " Impasses 2 : " 
                 + listeImpasses[explorateurX][explorateurY][2] 
                 + " Impasses 3 : " 
                 + listeImpasses[explorateurX][explorateurY][3]); */
                switch(dir){
                    case UP:
                        explorateurX++;
                        break;
                    case DOWN:
                        explorateurX--;
                        break;
                    case LEFT:
                        explorateurY++;
                        break;
                    case RIGHT:
                        explorateurY--;
                        break;
                }
            }
            estFaceAImpasse = false;
            for(int i = 0; i < 4; i++){
                if(explorateurX >= laby.LAB_SIZE || explorateurY >= laby.LAB_SIZE || explorateurX < 0 || explorateurY < 0){
                    // println("JE N'AI PAS TROUVE D'IMPASSE");
                    break;
                }
                if(listeImpasses[explorateurX][explorateurY][i] == 1){
                    if(i == 0){
                        if(dir == Direction.DOWN){
                            dirImpasse = Direction.UP; 
                            estFaceAImpasse = true;
                        }
                    }
                    if(i == 1){
                        if(dir == Direction.LEFT){
                            dirImpasse = Direction.RIGHT; 
                            estFaceAImpasse = true;
                        }
                    }
                    if(i == 2){
                        if(dir == Direction.RIGHT){
                            dirImpasse = Direction.LEFT;
                            estFaceAImpasse = true;
                        }
                    }
                    if(i == 3){
                        if(dir == Direction.UP){
                            dirImpasse = Direction.DOWN;
                            estFaceAImpasse = true;
                        }
                    }

                    
                }
            }
            switch(dir){ //on annule
                case UP:
                    explorateurX--;
                    break;
                case DOWN:
                    explorateurX++;
                    break;
                case LEFT:
                    explorateurY--;
                    break;
                case RIGHT:
                    explorateurY++;
                    break;
            }
            if(estFaceAImpasse){
                dirImpasse = dir;
            }
            // println("direction : " + dirImpasse + " estFaceAImpasse : " + estFaceAImpasse + " dir : " + dir);
            // println("posImpasse : " + new PVector(explorateurX, explorateurY));
            return new PVector(explorateurX, explorateurY);
        }
    }

    void teleporteDansUnLaby(int numetage, Direction dirarg, int coordXarg, int coordYarg){
        laby = pyra[numetage];
        joueur.setPosTeleporte(new PVector(25+50*(coordYarg), 25+50*(coordXarg), 25));
        //laby.toPShape();
        etage = numetage;
        if(coordXarg >= 0 && coordXarg < laby.LAB_SIZE && coordYarg >= 0 && coordYarg < laby.LAB_SIZE){
            coordX = coordXarg;
            coordY = coordYarg;
            oCoordX = coordXarg;
            oCoordY = coordYarg;
            dansLaby = true;
        }else{
            dansLaby = false;
        }
        globalCoordX = coordXarg;
        globalCoordY = coordYarg;
        dir = dirarg;
        switch(dirarg){
            case UP:
                this.angleZ = PI/2;
                this.oldAngleZ = angleZ;
                break;
            case DOWN:
                this.angleZ = -PI/2;
                this.oldAngleZ = this.angleZ;
                break;
            case LEFT:
                this.angleZ = 0;
                this.oldAngleZ = this.angleZ;
                break;
            case RIGHT:
                this.angleZ = PI;
                this.oldAngleZ = this.angleZ;
                break;
        }
        laby.visite(coordYarg, coordXarg);

        posHistory = new ArrayList<PVector>();
        posHistory.add(new PVector(coordXarg, coordYarg));
        momie.position = new PVector(-100, -100);
        departMomie = false;

        minimap0 = labyToMinimap(laby, sizeMap);
    }
}