 int limiteSupLaby; 
  int limiteInfLaby;
  float stepangle;
  float step;
  void avance(Direction dir){
    PVector posAAnim = joueur.pos;
    switch (dir) {
      case UP: 
          posAAnim = posAAnim.add(new PVector(0, step, 0)); globalCoordX += 1; break;
      case DOWN:
          posAAnim = posAAnim.sub(new PVector(0, step, 0)); globalCoordX -= 1; break;
      case LEFT:
          posAAnim = posAAnim.add(new PVector(step, 0, 0)); globalCoordY += 1; break;
      case RIGHT:
          posAAnim = posAAnim.sub(new PVector(step, 0, 0)); globalCoordY -= 1; break;
    }
    if(!(dansLaby)){
        departMomie = false;
    }
    
    joueur.setPosAnime(posAAnim);
    if(dansLaby){
      coordX = globalCoordX; 
      coordY = globalCoordY;
    }
  }
  PVector simuleAvance(Direction dir){
    PVector res = (new PVector(0,0));

    switch (dir) {
      case UP: 
          res = (new PVector(globalCoordX + 1, globalCoordY)); break;
      case DOWN:
          res = (new PVector(globalCoordX - 1, globalCoordY)); break;
      case LEFT:
          res = (new PVector(globalCoordX, globalCoordY + 1)); break;
      case RIGHT:
          res = (new PVector(globalCoordX, globalCoordY - 1)); break;
    }
    // println("SIMULE AVANCE : " + res.x + " " + res.y);
    return res;
  }
  boolean critereAvance(Direction dir){
    PVector poteentielNewCoord = simuleAvance(dir);
    // println("limiteSupLaby : " + limiteSupLaby + " limiteInfLaby : " + limiteInfLaby);
    // println("limiteSupMonde : " + limiteSupMonde + " limiteInfMonde : " + limiteInfMonde);
    dansLaby = (poteentielNewCoord.x >= 0 && poteentielNewCoord.y >= 0 && poteentielNewCoord.x < laby.LAB_SIZE+1 && poteentielNewCoord.y < laby.LAB_SIZE+1);
    // println("dansLaby : " + dansLaby);
    // println("coords : " + coordX + " " + coordY);
    // println("global : " + globalCoordX + " " + globalCoordY);

    boolean critereSortieMonde = (poteentielNewCoord.x > limiteInfMonde && poteentielNewCoord.y > limiteInfMonde && poteentielNewCoord.x < limiteSupMonde && poteentielNewCoord.y < limiteSupMonde);

    if(!critereSortieMonde){
      // println("CRITERE SORTIE MONDE LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }

    boolean critereSortieLaby = !dansLaby || (poteentielNewCoord.x >= limiteInfLaby && poteentielNewCoord.y >= limiteInfLaby && poteentielNewCoord.x <= limiteSupLaby && poteentielNewCoord.y <= limiteSupLaby);

    if(!critereSortieLaby){
      // println("CRITERE SORTIE LABY LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }

    boolean critereTaperPyramide = (
      dansLaby ||
      !((poteentielNewCoord.x >= limiteInfLaby-2 && poteentielNewCoord.x <= limiteSupLaby+2) && (poteentielNewCoord.y >= limiteInfLaby-2 && poteentielNewCoord.y <= limiteSupLaby+2)) ||
      //laisse faire si on est sorti/entré par l'entrée de pyra[0]
      (poteentielNewCoord.y == 1 && pyra[0] == laby) //aligné avec la sortie de pyra[0]
    );

    if(!critereTaperPyramide){
      // println("CRITERE TAPER PYRAMIDE LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }

    boolean critereTaperMur = (
      !dansLaby || (laby.labyrinthe[int(poteentielNewCoord.x)][int(poteentielNewCoord.y)] == ' ')
    );

    if(!critereTaperMur){
      laby.printLaby();
      // println("CRITERE TAPER MUR LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }

    boolean critereTaperMomie = (
      !dansLaby || !(poteentielNewCoord.x == momie.position.x && poteentielNewCoord.y == momie.position.y)
    );

    if(!critereTaperMomie){
      // println("momie : " + momie.position.x + " " + momie.position.y);
      // println("CRITERE TAPER MOMIE LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }
    boolean critereAnimation = joueur.chemin.size() == 0;

    if(!critereAnimation){
      // println("CRITERE ANIMATION LOUPÉ");
      dansLaby = (globalCoordX >= 0 && globalCoordY >= 0 && globalCoordX < laby.LAB_SIZE+1 && globalCoordY < laby.LAB_SIZE+1);
      return false;
    }

    return critereSortieMonde && critereSortieLaby && critereTaperPyramide && critereTaperMur && critereTaperMomie && !perdu && critereAnimation; //true en theorie
  }

  boolean critereBasDroite(Direction dir){
    PVector poteentielNewCoord = simuleAvance(dir);
    boolean critereSortirDuTerrain = dansLaby && !(poteentielNewCoord.x <= limiteSupLaby && poteentielNewCoord.y <= limiteSupLaby);
    //true si dans laby et le joueur a envie de sortir du terrain
    if(!critereSortirDuTerrain){
      // println("CRITERE SORTIR DU TERRAIN LOUPÉ");
    }

    if(poteentielNewCoord.x > laby.LAB_SIZE-1 || poteentielNewCoord.y > laby.LAB_SIZE-1 || poteentielNewCoord.x < 0 || poteentielNewCoord.y < 0){
      //devrait pas arriver mais au cas où
      return false;
    }

    boolean criterePasTaperMur = (
      dansLaby && (laby.labyrinthe[int(poteentielNewCoord.x)][int(poteentielNewCoord.y)] == ' ')
    );
    //true si dans laby et le joueur n'a pas tapé un mur
    if(!criterePasTaperMur){
      laby.printLaby();
      // println("CRITERE PAS TAPER MUR LOUPÉ");
    }

    return critereSortirDuTerrain && criterePasTaperMur;
  }

  boolean critereHautGauche(Direction dir){
    PVector poteentielNewCoord = simuleAvance(dir);

    boolean critereSortirDuTerrain = dansLaby && !(poteentielNewCoord.x >= limiteInfLaby && poteentielNewCoord.y >= limiteInfLaby);
    //true si dans laby et le joueur a envie de sortir du terrain
    if(!critereSortirDuTerrain){
      // println("CRITERE SORTIR DU TERRAIN LOUPÉ");
    }

    if(poteentielNewCoord.x > laby.LAB_SIZE-1 || poteentielNewCoord.y > laby.LAB_SIZE-1 || poteentielNewCoord.x < 0 || poteentielNewCoord.y < 0){
      //devrait pas arriver mais au cas où
      return false;
    }

    boolean criterePasTaperMur = (
      dansLaby && (laby.labyrinthe[int(poteentielNewCoord.x)][int(poteentielNewCoord.y)] == ' ')
    );
    //true si dans laby et le joueur n'a pas tapé un mur
    if(!criterePasTaperMur){
      laby.printLaby();
      // println("CRITERE PAS TAPER MUR LOUPÉ");
    }

    return critereSortirDuTerrain && criterePasTaperMur;
  }

  Direction oppositeDir(Direction dir){
    switch(dir){
      case UP:
        return Direction.DOWN;
      case DOWN:
        return Direction.UP;
      case LEFT:
        return Direction.RIGHT;
      case RIGHT:
        return Direction.LEFT;
    }
    return Direction.UP;
  }
  Direction tourneADroite(Direction dir){
    switch(dir){
      case UP:
        return Direction.RIGHT;
      case RIGHT:
        return Direction.DOWN;
      case DOWN:
        return Direction.LEFT;
      case LEFT:
        return Direction.UP;
    }
    return Direction.UP;
  }
  Direction tourneAGauche(Direction dir){
    switch(dir){
      case UP:
        return Direction.LEFT;
      case LEFT:
        return Direction.DOWN;
      case DOWN:
        return Direction.RIGHT;
      case RIGHT:
        return Direction.UP;
    }
    return Direction.UP;
  }
void keyPressed() {
  limiteSupLaby = laby.LAB_SIZE-2;
  limiteInfLaby = 1;
  stepangle = PI/2;
  step = 50;

  if(laby.numetage == 0){limiteInfLaby = 0;}




  // tourne a droite
  if (keyCode == RIGHT) {
    joueur.setAngleAnime(joueur.angleZ + stepangle);
    /* cpt = cptMaxVal;
    joueur.angleZ += stepangle; */
    switch(dir){
      case UP:
        dir = Direction.RIGHT; break;
      case RIGHT:
        dir = Direction.DOWN; break;
      case DOWN:
        dir = Direction.LEFT; break;
      case LEFT:
        dir = Direction.UP; break;
    }
  } 
  // tourne a gauche
  else if (keyCode == LEFT) {
    joueur.setAngleAnime(joueur.angleZ - stepangle);
    /* cpt = cptMaxVal;
    joueur.angleZ -= stepangle; */
    switch(dir){
      case UP:
        dir = Direction.LEFT; break;
      case LEFT:
        dir = Direction.DOWN; break;
      case DOWN:
        dir = Direction.RIGHT; break;
      case RIGHT:
        dir = Direction.UP; break;
    }
  }
  //decole
  else if (keyCode == UP && debug){
    joueur.setPosAnime(joueur.pos.add(new PVector(0, 0, step)));
    /* cpt = cptMaxVal;
    pos.z += step; */
  } 
  // descend
  else if (keyCode == DOWN && debug){
    joueur.setPosAnime(joueur.pos.sub(new PVector(0, 0, step)));
    /* cpt = cptMaxVal;
    pos.z -= step; */
  } 
  // avance
  else if (key == 'z') {
    //! ATTENTION MISE EN GARDE -> LES COORDS SONT INTERDITES D'ALLER PLUS LOIN DE LABSIZE-2 ET 1 (ou 0 au 1er etage) POUR NE PAS ALLER SUR LES CASES D'ENTREE ET DE SORTIE ET NE PAS PERTURBER L'ANIMATION
    if(critereAvance(dir)){
      avance(dir);
    }else if(critereBasDroite(dir)){
      if(etage%2 == 0){
        animationStageMonter = true;
      }else{
        animationStageDescendre = true;
      }
    }else if(critereHautGauche(dir)){
      if(etage%2 == 0){
        animationStageDescendre = true;
      }else{
        animationStageMonter = true;
      }
    }
  }
  // gauche
  else if (key == 'q'){
    if(critereAvance(tourneAGauche(dir))){
      avance(tourneAGauche(dir));
    }
  } 
  // recule
  else if (key == 's') {
    if(critereAvance(oppositeDir(dir))){
      avance(oppositeDir(dir));
    }
  } 
  // droite
  else if (key == 'd'){
    if(critereAvance(tourneADroite(dir))){
      avance(tourneADroite(dir));
    }
  } 

  // changement de teinte (passage en mode mur coloré)
  else if(key == 't' && abs(joueur.oldPos.z - z) == 0){ 
      tintFlag = !tintFlag; 
      // laby0 = labyToPShape(laby, laby.LAB_SIZE, "texture");
      // laby.toPShape(50, "texture");

  }

  else if(key == 'l'){
    levelOfLight = (levelOfLight) % 3 + 1;
  }

  else if(keyCode == 9){
    debug = !debug;
    if(debug) println("mode debug activée");
    else println("mode debug désactivée");
  }
  else if (keyCode > 47 && keyCode < 58){ 
    if(keyCode-48 >= coordDiapo.size() || keyCode-48 >= dirDiapo.size()){println("le tableau n'est pas assez grand"); return;}
    PVector coord_ = coordDiapo.get(keyCode-48);
    Direction dir_ = dirDiapo.get(keyCode-48);
    println("coord_ = ", coord_, ", dir_ = ", dir_);
    joueur.teleporteDansUnLaby((int)coord_.z, dir_, (int)coord_.x, (int)coord_.y);

  }





  else if(keyCode == 8){exit();}
  // // println("\nkeyCode = " + keyCode);
  // affichage des informations
  println("----------------------------------------------------------------------------------------------");
    println("coordX: ", globalCoordX, ", coordY: ", globalCoordY);//, ", pos: ", joueur.pos);
    println("numetage:", etage);
    println("dir: ", dir);
    println("coordDiapo.add(new PVector(", globalCoordX, "," , globalCoordY, ",", etage, "));");
    println("dirDiapo.add(Direction."+ dir, ");");
    
    // println("angleX: ", angleX);
  println("----------------------------------------------------------------------------------------------");
  // affichage du labyrinthe avec la position du joueur
  // for(int i = 0; i < laby.LAB_SIZE; i++){
  //   for(int j = 0; j < laby.LAB_SIZE; j++){
  //     if(i == coordX && j == coordY)
  //       print("\033[92mX\033[0m");
  //     else if(laby.sides[i][j][0] != 0)
  //       print("\033[91m1\033[0m");
  //     else if(laby.sides[i][j][1] != 0)
  //       print("\033[91m2\033[0m");
  //     else if(laby.sides[i][j][2] != 0)
  //       print("\033[91m3\033[0m");
  //     else if(laby.sides[i][j][3] != 0)
  //       print("\033[91m4\033[0m");
  //     else
  //       print(laby.labyrinthe[i][j]);
  //   }
  //   // println();
  // }
  println("keycode = " + keyCode + ", key = " + key);
  

}