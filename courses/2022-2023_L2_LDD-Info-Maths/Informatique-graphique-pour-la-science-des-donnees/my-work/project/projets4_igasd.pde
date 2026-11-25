ArrayList<PVector> coordDiapo = new ArrayList<PVector>();
ArrayList<Direction> dirDiapo = new ArrayList<Direction>();






PGraphics winText;
PGraphics looseText;

PImage pocketLight;
PImage compas;
PImage hand;
PImage wall;
PImage wood;
PImage stones;
PImage floor;
PImage wallnmap;
PImage wallheightmap;
PImage sand;
PImage heart;
PImage heartFull;
PImage floornmap;
PImage coffreItem;

PShape chest;
PShape sarcophage;

PShape laby0;
PShape minimap0;
PShape pyramide0;
PShape desert0;
float amplitudeDesert;
float frequenceDesert;

enum Direction {UP, DOWN, LEFT, RIGHT}

Labyrinthe laby;
Direction dir = Direction.UP;

// choix des coordonnées de depart
int coordX = 0;
int coordY = 1;

int oCoordX = coordX;
int oCoordY = coordY;

int globalCoordX = coordX;
int globalCoordY = coordY;

  //coordonnées de depart de la camera
  float x = 25 + (coordX+1)*50;
  float y = 25 + (coordY-1)*50;
  float z = 25;

  // angles de rotation de la camera
  float angleX = 0;
  float angleY = PI;
  float angleZ = PI/2;

  int cpt = 0; //cpt animation pour la momie
  int cptMaxVal = 10;
  int resSec = 0;
Joueur joueur;


int sizeMap = 20;
int levelOfLight = 1;

boolean tintFlag = false;
boolean minimap = false;
boolean gagne = false;
boolean perdu = false;

PShader shader3d;
Minuteur timerCoffre;
Minuteur timerEnd;

int pyramideHeight = 3;
int topLabySize = 3;
Labyrinthe[] pyra = new Labyrinthe[pyramideHeight];
int etage = 0;
int nbMarche = 15;
int nbVieMax = pyramideHeight+1;
int nbVie = nbVieMax;

Momie momie;
//FIFO de positions pour l'historique des mouvements du joueur
ArrayList<PVector> posHistory = new ArrayList<PVector>();
int nbCoupsDavance = 3;
boolean departMomie = false;

boolean animationStageMonter = false;
boolean animationStageDescendre = false;
boolean monte;
boolean debug = false;


boolean estFaceAImpasse;
Direction dirImpasse;
PVector posImpasse;

boolean dansLaby = true;
int limiteInfMonde = -100;
int limiteSupMonde = 100;

PShape testShape;

PShader shaderdefault;
PShader shaderSol;

boolean lowPolyHand = false;

void setup() { 
  

  // touche 0
  coordDiapo.add(new PVector( 0 , 1 , 0 ));
  dirDiapo.add(Direction.UP );

  // touche 1 Dehors/pyramide
  coordDiapo.add(new PVector( -21 , 1 , 0 ));
  dirDiapo.add(Direction.UP );

  // touche 2 Shader
  coordDiapo.add(new PVector( 1 , 4 , 0 ));
  dirDiapo.add(Direction.DOWN );

  // touche 3 Changement de niveau
  coordDiapo.add(new PVector( 7 , 7 , 0 ));
  dirDiapo.add(Direction.LEFT );

  // touche 4 Impasse / Sarcophage
  coordDiapo.add(new PVector( 5 , 3 , 0 ));
  dirDiapo.add(Direction.DOWN );

  // touche 5 Coffre
  coordDiapo.add(new PVector( 3 , 2 , 2 ));
  dirDiapo.add(Direction.LEFT );



  frameRate(60);
  randomSeed(2);
  noiseSeed(100);
  // size(800, 600, P3D);
  fullScreen(P3D);  
  shaderSol = loadShader("texLightFrag.glsl", 
                            "texLightVert.glsl");
  shaderdefault = loadShader("texLightFrag.glsl", 
                            "texLightVert.glsl");
  // Chargement des textures
  wall = loadImage("./src/stones.jpg");
  wood = loadImage("./src/wood.jpg");
  stones = loadImage("./src/stones2.jpg");
  wallnmap = loadImage("./src/wallnmap.png");
  wallheightmap = loadImage("./src/height.png");
  floor = loadImage("./src/floor.png");
  floornmap = loadImage("./src/floornmap.png");
  // Chargement des images
  pocketLight = loadImage("./src/light.png");
  compas = loadImage("./src/compas.png");
  hand = loadImage("./src/hand.png");
  coffreItem = loadImage("./src/chest/chest_item.png");
  sand = loadImage("./src/sand.jpg");
  heart = loadImage("./src/heart.png");
  heartFull = loadImage("./src/heartFull.png");
  shaderdefault.set("wallnmap", wallnmap);
  shaderSol.set("wallnmap", floornmap);
  textureMode(NORMAL);
  noCursor();
  smooth();
  
  chest = loadShape("./src/chest/chest.obj");
  //chest = createSphere(color(255,0,0));
  chest.scale(3);
  // Creation du labyrinthe
  for(int i = pyramideHeight-1; i >= 0; i--){
    pyra[i] = new Labyrinthe(topLabySize + (pyramideHeight-i)*2, i);
    pyra[i].generate();
    pyra[i].toPShape();
    // pyraShape[i] = labyToPShape(pyra[i], pyra[i].LAB_SIZE, "texture");
  }
  laby = pyra[etage];
  // On visite la case de depart
  laby.visite(coordY, coordX);

  // Creation du labyrinthe en PShape
  // laby.toPShape();

  // Creation du minimap
  minimap0 = labyToMinimap(laby, sizeMap);
  pyramide0 = new Pyramide(pyra[0].LAB_SIZE, pyramideHeight*2, nbMarche).generate();
  pyramide0.translate(0, 0 , -100);
  sarcophage = loadShape("./src/sarcophage/10808_Sarcophagus_LOD1.obj");
  //sarcophage = createSphere(color(0,255,0));
  sarcophage.scale(25);
  sarcophage.rotateY(-PI/2);
  // sarcophage.rotateZ(PI/2);
  sarcophage.translate(35, 15, 35);
  
  

  // Texte de victoire
  winText = createGraphics(width, height, P2D);
  winText.beginDraw();
  winText.fill(0,255,0);
  winText.textFont(createFont("./src/typewritter.ttf", 150));
  winText.textAlign(CENTER);
  winText.text("You Win !", width/2, height/2+winText.textAscent()/2);
  winText.endDraw();

  // Texte de defaite
  looseText = createGraphics(width, height, P2D);
  looseText.beginDraw();
  looseText.fill(255,0,0);
  looseText.textFont(createFont("./src/typewritter.ttf", 150));
  looseText.textAlign(CENTER);
  looseText.text("Game Over !", width/2, height/2+looseText.textAscent()/2);
  looseText.endDraw();

 

  momie = new Momie(new PVector(-1, -1),10,20);
  joueur = new Joueur();

  posHistory.add(new PVector(joueur.pos.x, joueur.pos.y));
  // testShape = createechelle(10, 200, 50, color(0, 255, 0), color(0, 0, 255));
  amplitudeDesert = 150;
  frequenceDesert = 1/10.;
  desert0 = createFloorDesert(1, amplitudeDesert, frequenceDesert);


  
  for(int i = 1; i <= pyramideHeight; i++){
    resSec += i*4;
  }
  timerCoffre = new Minuteur(resSec);
  timerEnd = new Minuteur(5);
}


void draw(){
  posImpasse = joueur.setEstFaceAImpasseDirAndRetPos(dir);
  
  if(dansLaby && !(coordY == 1 && etage == 0 && dir == Direction.DOWN)){
    background(0);
  }
  else{
    // ciel
    background(0, 100, 255);
  }



  //  Check change position
  if(oCoordX != coordX || oCoordY != coordY){ 
    laby.visite(coordY, coordX);
    minimap0 = labyToMinimap(laby, sizeMap);
    posHistory.add(new PVector(coordX, coordY));
    if(posHistory.size() > nbCoupsDavance) departMomie = true;
  }

  oCoordX = coordX; oCoordY = coordY;

  // angleX en fonction de la position de la souris
  angleX = PI/4 - map(mouseY, 0, height, 0, PI-PI/4);
  
  float xdirvect = 50*cos(angleX)*cos(joueur.oldAngleZ);
  float ydirvect = 50*cos(angleX)*sin(joueur.oldAngleZ);
  float zdirvect = 50*sin(angleX);

  beginCamera();
    camera(joueur.oldPos.x,joueur.oldPos.y,joueur.oldPos.z, joueur.oldPos.x + xdirvect, joueur.oldPos.y + ydirvect, joueur.oldPos.z + zdirvect, 0, 0, -1);
    perspective(PI/3.0, float(width)/float(height), 1, 10000);
  endCamera();



  // spotlight effet lampe de poche (pointe vers la direction de la camera)
  float r, g, b;
  // tinte les murs si appuis sur la touche T
  if(tintFlag && dansLaby) { 
    r = map(coordY, 0, laby.LAB_SIZE-1, 0, 255);
    g = map(coordX, 0, laby.LAB_SIZE-1, 0, 255);
    b = map(laby.LAB_SIZE-coordY, 0, laby.LAB_SIZE-1, 0, 255);
    
  }
  else { r = g = 255; b = 180; }
  
  // effet de scintillement de la lampe
  float rand = map(noise(millis()/500.0), 0, 1, 0.3, 1);

  //TODO : deplacement de la lampe avec la souris (ne fonctionne pas trop)
  float axm = map(mouseX, 0, width, -PI/6,  PI/6); //angle de la souris
  float aym = map(mouseY, 0, height, -PI/6, PI/6);
  float lxdirvect = 50*cos(angleY)*cos(joueur.oldAngleZ+axm); //direction lampe
  float lydirvect = 50*cos(angleY)*sin(joueur.oldAngleZ+axm);
  float lzdirvect = 50*sin(angleX+aym);
  // pushMatrix();
  if(dansLaby){
    push();
    lightFalloff(0.3/levelOfLight, 0.001/levelOfLight, 0.0001/levelOfLight);
    //spotLight(r*rand, g*rand, b*rand, joueur.oldPos.x, joueur.oldPos.y, joueur.oldPos.z, lxdirvect, lydirvect,  sin(z)*50 , PI/6, 0);
    pointLight(r*rand, g*rand, b*rand, joueur.oldPos.x, joueur.oldPos.y, joueur.oldPos.z);
    pop();
  }else{
    pointLight(r,g,b, x, y-1000, z+1000);
    ambientLight(r,g,b, x, y-1000, z+1000);
  }

  if(estFaceAImpasse){
    float rotationSarcophage = 0;
    float sarcophageOffsetX = 0;
    float sarcophageOffsetY = 0;
    color colorLightImpasse = color(255, 255, 255);
    float animationOffsetX = 0;
    float animationOffsetY = 0;
    float animationOffset = 10;
    float speedAnimation = 120;
    float animationPhase = sin(map(frameCount%speedAnimation, 0, speedAnimation, 0, 2*PI));
    switch(dirImpasse){
      case UP:
        colorLightImpasse = color(255, 0, 0);
        rotationSarcophage = PI/2;
        sarcophageOffsetX = 50;
        animationOffsetX = animationOffset*animationPhase;
        break;
      case DOWN:
        colorLightImpasse = color(0, 255, 0);
        rotationSarcophage = -PI/2;
        sarcophageOffsetY = 50;
        animationOffsetX = animationOffset*animationPhase;
        break;
      case LEFT:
        colorLightImpasse = color(0, 0, 255);
        rotationSarcophage = 0;
        animationOffsetY = animationOffset*animationPhase;
        break;
      case RIGHT:
        colorLightImpasse = color(255, 255, 0);
        rotationSarcophage = PI;
        sarcophageOffsetX = 50;
        sarcophageOffsetY = 50;
        animationOffsetY = animationOffset*animationPhase;
        break;
    }
    pointLight(red(colorLightImpasse), green(colorLightImpasse), blue(colorLightImpasse), 50*posImpasse.y + 25, 50*posImpasse.x + 25, 75);
    pushMatrix();
      
      translate(50*posImpasse.y+sarcophageOffsetX+animationOffsetX, 50*posImpasse.x+sarcophageOffsetY+animationOffsetY, 0);
      rotateZ(rotationSarcophage);
      shape(sarcophage);
    popMatrix();
  }
  // popMatrix();
  // le mode minimap du labyrinthe (on verifie si on a décoller)
  if(joueur.oldPos.z - z > 100){   //quand on appuis sur une touche qui fait monter ou descendre la camera
    // laby0 = labyToPShape(laby, laby.LAB_SIZE, "minimap");
    if(!minimap){
      print("je passe minimap");
      laby.toPShape(50, 100, "minimap");
    }

    minimap = true;
    // le petit oiseau
    push();
      translate(joueur.oldPos.x, joueur.oldPos.y, z);
      fill(0, 255, 0);
      noStroke();
      lights();
      // Sphere pour le corp de l'oiseau
      sphere(12.5);
    
      //le bec de l'oiseau
      beginShape(TRIANGLE_FAN);
        // direction du bec
        switch (dir) {
          case UP: 
            vertex(0, 25, 0);break;
          case DOWN: 
            vertex(0, -25, 0);break;
          case LEFT: 
            vertex(25, 0, 0);break;
          case RIGHT: 
            vertex(-25, 0, 0);break;
        }
        for(int i = 0; i <= 100; i++){
            float angle = map(i, 0, 100, 0, TWO_PI);
            float x = 12.5 * cos(angle);
            float y = 12.5 * sin(angle);
            switch (dir) {
              case UP: 
                vertex(x, 0, y);break;
              case DOWN: 
                vertex(x, 0, y);break;
              case LEFT: 
                vertex(0, x, y);break;
              case RIGHT: 
                vertex(0, x, y);break;
            }
        }
      endShape();
    pop();
  }
  else if(minimap){ 
    minimap = false;
    laby.toPShape();
    print("je passe laby");
    // laby0 = doubleHeightLabyPshape(laby, laby.LAB_SIZE, "texture");
  }
  if(cpt != 0){             
    //print("anim"+cpt);                             //animation handler
    cpt--;
    if(momie.mvtDir.x == 0 && momie.mvtDir.y == 0){
      momie.mvtDir = PVector.sub(momie.position, momie.oldPos);
      momie.mvtDir = momie.mvtDir.div(cptMaxVal);                    //define one animation step
    }                    
    momie.oldPos.add(momie.mvtDir);                      //add animation step
  }else{                                                 //end animation
    momie.oldPos = momie.position.copy();
    momie.mvtDir = new PVector(0,0);
  }
  joueur.animateMarche();
  joueur.animateAngle();
  
  
  

  // le labyrinthe
  //avec shaders perso
  if(!minimap) shader(shaderdefault);
    shape(laby.wallShape);
    if(dansLaby){
      shape(laby.couloirsShape);
    }
  if(!minimap) resetShader();
  //sans shaders perso
    shape(laby.floorShape);
  if(dansLaby){
    shape(laby.endEchelleShape);
    shape(laby.startEchelleShape);
    if(!gagne) {shape(laby.treasureShape); println("j'ai fais apparaitre le coffre, numetage =", laby.numetage);}
    // // println("coordX : "+coordX+ " coordY : " + coordY +" etage : "+etage+" dir : "+dir);
    if (coordY == 1 && etage == 0 && dir == Direction.DOWN){
      shape(desert0);
      
    }

  }else{
    shape(desert0);
    push();
      translate(-100, -100, 0);
      shape(pyramide0);
    pop();
  }
  
  push();
  //translate(x, y, z);
  translate(y+50*(momie.oldPos.y), x+50*(momie.oldPos.x-1), z);
  rotateZ(PI/2 + momie.angleZ);
  if(departMomie) 
    shape(momie.pshape);
  else
    momie.position = new PVector(-100,-100);
    
  //shape(testShape);
  pop();
  //resetShader();
  
  hint(DISABLE_DEPTH_TEST);

    push();
      // desactivation de la caméra
      camera();
      
      // La minimap
      push();
        noLights();
        ortho();
        shape(minimap0);
      pop();
      
      // La lampe de poche
      image(pocketLight, width-width/4+map(mouseX, 0, width, -50, 50), height-150, 200, 200);
      // la main
      image(hand, 0, height-200, 300, 300);

      // La bousole
      pushMatrix();
        translate(210, height-130);
        switch (dir) {
          case UP: 
            rotate(PI);break;
          case DOWN: 
            rotate(0);break;
          case LEFT: 
            rotate(3*PI/2);break;
          case RIGHT: 
            rotate(PI/2);break;
        }
        imageMode(CENTER);
        image(compas, 0, 0, 120, 120);
      popMatrix();

      // le petit oiseau
      push();
        translate(sizeMap*(coordY+0.5), sizeMap*(coordX+0.5), 0);
          fill(0, 255, 0);
          noStroke();
          lights();

          sphere(sizeMap*0.9/2.0);
          // La fleche
          beginShape(TRIANGLE_FAN);
            switch (dir) {
              case UP: 
                vertex(0, sizeMap, 0);break;
              case DOWN: 
                vertex(0, -sizeMap, 0);break;
              case LEFT: 
                vertex(sizeMap, 0, 0);break;
              case RIGHT: 
                vertex(-sizeMap, 0, 0);break;
            }
            for(int i = 0; i <= 100; i++){
                float angle = map(i, 0, 100, 0, TWO_PI);
                float x = sizeMap*0.9/2.0 * cos(angle);
                float y = sizeMap*0.9/2.0 * sin(angle);
                switch (dir) {
                  case UP: 
                    vertex(x, 0, y);break;
                  case DOWN: 
                    vertex(x, 0, y);break;
                  case LEFT: 
                    vertex(0, x, y);break;
                  case RIGHT: 
                    vertex(0, x, y);break;
                }
            }
          endShape();
        pop();
        
        
        // Le texte de victoire
        if(animationStageMonter){ 
          //! Attention : le critere doit imperativement changer et se basser non pas sur la position mais le deplacement -> deplacement va interdire le changement de position mais detecter le changement de niveau et en faire quelque chose
            animationStageMonter = false;
            if(etage < pyra.length-1){
              etage++;
              // print("etage = " + etage);
              laby = pyra[etage];
              // laby.toPShape();
              print("je monte de niveau");

              laby.visite(coordY, coordX);
              if(etage % 2 == 0){
                joueur.pos = new PVector(x, y+50, z);
                joueur.oldPos = joueur.pos.copy();
                coordX = 1;
                coordY = 1;
                oCoordX = 1;
                oCoordY = 1;
                globalCoordX = 1;
                globalCoordY = 1;
                /* dir = Direction.DOWN;
                angleX = 0;
                angleY = PI;
                angleZ = -PI/2;
                oldAngleZ = angleZ; */
                laby.visite(coordY, coordX);
                joueur.setPosTeleporte(joueur.pos.add(new PVector(0,0,-100)));
                joueur.addVectorToChemin(new PVector(0,0,0));
                joueur.addVectorToChemin(new PVector(0,-45,0));
                joueur.addVectorToChemin(new PVector(0,0,100));
                joueur.addVectorToChemin(new PVector(0,45,0));
              }else{
                //opposite side
                coordX = laby.LAB_SIZE-2;
                coordY = laby.LAB_SIZE-2;
                oCoordX = laby.LAB_SIZE-2;
                oCoordY = laby.LAB_SIZE-2;
                globalCoordX = laby.LAB_SIZE-2;
                globalCoordY = laby.LAB_SIZE-2;
                joueur.pos = new PVector(x+50*(coordY-1), y+50*(coordX), z);
                joueur.oldPos = joueur.pos.copy();
                /* dir = Direction.LEFT;
                angleX = 0;
                angleY = PI;
                angleZ = -PI;
                oldAngleZ = angleZ; */
                laby.visite(coordY, coordX);
                joueur.setPosTeleporte(joueur.pos.add(new PVector(0,0,-100)));
                joueur.addVectorToChemin(new PVector(0,0,0));
                joueur.addVectorToChemin(new PVector(45,0,0));
                joueur.addVectorToChemin(new PVector(0,0,100));
                joueur.addVectorToChemin(new PVector(-45,0,0));
              }
              posHistory = new ArrayList<PVector>();
              posHistory.add(new PVector(coordX, coordY));
              momie.position = new PVector(-1, -1);
              departMomie = false;

              minimap0 = labyToMinimap(laby, sizeMap);
              
              // println("etage : " + etage, "taille : " + laby.LAB_SIZE);
              monte = true;
            }else{
              laby.visiteAll();
              minimap0 = labyToMinimap(laby, sizeMap);
              gagne = true;
              

              //dansLaby = false;
              //?retiré car theoriquement on ne sort pas du labyrinthe par le haut
            }
        }
        
        if(animationStageDescendre){
          animationStageDescendre = false;
          etage--;
              laby = pyra[etage];
              // laby.toPShape();
              print("je descend de niveau");

              laby.visite(coordY, coordX);
                            

              if(etage % 2 == 1){
                joueur.pos = new PVector(x, y+50, z);
                joueur.oldPos = joueur.pos.copy();
                coordX = 1;
                coordY = 1;
                oCoordX = 1;
                oCoordY = 1;
                globalCoordX = 1;
                globalCoordY = 1;
                /* dir = Direction.DOWN;
                angleX = 0;
                angleY = PI;
                angleZ = -PI/2;
                oldAngleZ = angleZ; */
                laby.visite(coordY, coordX);
                joueur.setPosTeleporte(joueur.pos.add(new PVector(0,0,100)));
                joueur.addVectorToChemin(new PVector(0,0,0));
                joueur.addVectorToChemin(new PVector(0,-45,0));
                joueur.addVectorToChemin(new PVector(0,0,-100));
                joueur.addVectorToChemin(new PVector(0,45,0));
              }else{
                //opposite side
                coordX = laby.LAB_SIZE-2;
                coordY = laby.LAB_SIZE-2;
                oCoordX = laby.LAB_SIZE-2;
                oCoordY = laby.LAB_SIZE-2;
                globalCoordX = laby.LAB_SIZE-2;
                globalCoordY = laby.LAB_SIZE-2;
                joueur.pos = new PVector(x+50*(coordY-1), y+50*(coordX), z);
                joueur.oldPos = joueur.pos.copy();
                /* dir = Direction.LEFT;
                angleX = 0;
                angleY = PI;
                angleZ = -PI;
                oldAngleZ = angleZ; */
                laby.visite(coordY, coordX);
                joueur.setPosTeleporte(joueur.pos.add(new PVector(0,0,100)));
                joueur.addVectorToChemin(new PVector(0,0,0));
                joueur.addVectorToChemin(new PVector(45,0,0));
                joueur.addVectorToChemin(new PVector(0,0,-100));
                joueur.addVectorToChemin(new PVector(-45,0,0));
              }
              posHistory = new ArrayList<PVector>();
              posHistory.add(new PVector(coordX, coordY));
              momie.position = new PVector(-1, -1);
              departMomie = false;

              minimap0 = labyToMinimap(laby, sizeMap);
              
              // println("etage : " + etage, "taille : " + laby.LAB_SIZE);


              monte = false;
        }
          
    if(gagne && !perdu){
      
      timerCoffre.update();
      if(timerCoffre.isNull()){
        perdu = true;
      }
      else{ 
        image(timerCoffre.text, width-80, 90);
        image(coffreItem, width-140, 90, 70, 70);
        timerCoffre.log();
        if(!dansLaby){
          timerEnd.update();
          if(timerEnd.isNull()){
            exit();
          }
          image(winText, width/2, height/2);
        }
      }

    }
    for(int i = 0; i < nbVieMax - nbVie; i++){ 
      image(heart, width-20 - i*30, 20, 30, 30);
    }
    for(int i = nbVieMax - nbVie; i < nbVieMax; i++){ 
      image(heartFull, width-20 - i*30, 20, 30, 30);
    }
    if(nbVie == 0){ perdu = true;}

    if(perdu){
      timerEnd.update();
      if(timerEnd.isNull()){
        exit();
      }
      image(looseText, width/2, height/2);
    }
    pop();


  
  hint(ENABLE_DEPTH_TEST);

  if(posHistory.size() > 1 && dansLaby && (frameCount/60) != ((frameCount+1)/60)){
    //? Fait bouger la momie uniquement dans le labyrinthe, c'est bien
    // println("Position jour : " + coordX + " " + coordY, "Position de la momie : " + momie.position.x + " " + momie.position.y);
    if(departMomie) posHistory.remove(0);
    momie.position = posHistory.get(0);
    // println(posHistory.size());
    if(posHistory.get(0).x == coordX && posHistory.get(0).y == coordY){
      // println("GAME OVER");
      nbVie--;
      gagne = false;
      timerCoffre.set(resSec);
      if(etage%2 == 0){

              dir = Direction.UP;
              joueur.angleZ = PI/2;
              joueur.oldAngleZ = joueur.angleZ; 
              if(etage == 0){
                coordX = 0;
                coordY = 1;
                oCoordX = 0;
                oCoordY = 1;
                globalCoordX = 0;
                globalCoordY = 1;
                joueur.setPosTeleporte(new PVector(50+25, 25, 25));
                // dir = Direction.UP;
                posHistory = new ArrayList<PVector>();
                posHistory.add(new PVector(coordX, coordY));
                momie.position = new PVector(-1, -1);
                departMomie = false;

              }
              else{
                coordX = 1;
                coordY = 1;
                oCoordX = 1;
                oCoordY = 1;
                globalCoordX = 1;
                globalCoordY = 1;
                joueur.setPosTeleporte(new PVector(50+25, 50+25, 25));
                // dir = Direction.UP;
                posHistory = new ArrayList<PVector>();
                posHistory.add(new PVector(coordX, coordY));
                momie.position = new PVector(-1, -1);
                departMomie = false;
              }
      }
      else{
              coordX = laby.LAB_SIZE-2;
              coordY = laby.LAB_SIZE-2;
              oCoordX = laby.LAB_SIZE-2;
              oCoordY = laby.LAB_SIZE-2;
              globalCoordX = laby.LAB_SIZE-2;
              globalCoordY = laby.LAB_SIZE-2;
              dir = Direction.RIGHT;
              joueur.angleZ = PI;
              joueur.oldAngleZ = joueur.angleZ;
              joueur.setPosTeleporte(new PVector((laby.LAB_SIZE-2)*50+25, (laby.LAB_SIZE-2)*50+25, 25));
              // dir = Direction.RIGHT;
              posHistory = new ArrayList<PVector>();
              posHistory.add(new PVector(coordX, coordY));
              momie.position = new PVector(-1, -1);
              departMomie = false;
      }
    }
    momie.angleZ = joueur.angleZ + PI/2;
    cpt = cptMaxVal;
  }

}