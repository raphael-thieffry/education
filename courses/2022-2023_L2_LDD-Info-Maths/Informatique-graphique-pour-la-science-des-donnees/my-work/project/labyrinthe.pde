public class Labyrinthe {
  int LAB_SIZE;
  char labyrinthe [][];
  int sides [][][];
  boolean[][] visited;
  PShape wallShape, floorShape, endEchelleShape, startEchelleShape, couloirsShape, treasureShape;
  int numetage;

  // int hauteurechelle = 200;
  public Labyrinthe () {
    this.LAB_SIZE = 21; 
    this.wallShape = createShape(GROUP);
    this.floorShape = createShape(GROUP);
    visited = new boolean[this.LAB_SIZE][this.LAB_SIZE];
    for (int i = 0; i < this.LAB_SIZE; i++) {
      for (int j = 0; j < this.LAB_SIZE; j++) {
        visited[i][j] = false;
      }
    }
  }

  public Labyrinthe (int size, int numetage) {
    this.LAB_SIZE = size;
    this.wallShape = createShape(GROUP);
    this.floorShape = createShape(GROUP);
    visited = new boolean[this.LAB_SIZE][this.LAB_SIZE];
    for (int i = 0; i < this.LAB_SIZE; i++) {
      for (int j = 0; j < this.LAB_SIZE; j++) {
        visited[i][j] = false;
      }
    }
    this.numetage = numetage;
  }

  void printLaby(){
    for(int i = 0; i < laby.LAB_SIZE; i++){
      for(int j = 0; j < laby.LAB_SIZE; j++){
          print(laby.labyrinthe[i][j]);
      }
    // println();
  }
  }

  public void generate(){
    labyrinthe = new char[this.LAB_SIZE][this.LAB_SIZE];
    sides = new int[this.LAB_SIZE][this.LAB_SIZE][4];
    int todig = 0;
    for (int j=0; j<this.LAB_SIZE; j++) {
      for (int i=0; i<this.LAB_SIZE; i++) {
        sides[j][i][0] = 0;
        sides[j][i][1] = 0;
        sides[j][i][2] = 0;
        sides[j][i][3] = 0;
        if (j%2==1 && i%2==1) {
          labyrinthe[j][i] = '.';
          todig ++;
        } else{
          labyrinthe[j][i] = '#';
        }
      }
    }
  

  int gx = 1;
  int gy = 1;
  while (todig>0 ) {
    int oldgx = gx;
    int oldgy = gy;
    int alea = floor(random(0, 4)); // selon un tirage aleatoire
    if      (alea==0 && gx>1)          gx -= 2; // le fantome va a gauche
    else if (alea==1 && gy>1)          gy -= 2; // le fantome va en haut
    else if (alea==2 && gx<this.LAB_SIZE-2) gx += 2; // .. va a droite
    else if (alea==3 && gy<this.LAB_SIZE-2) gy += 2; // .. va en bas

    if (labyrinthe[gy][gx] == '.') {
      todig--;
      labyrinthe[gy][gx] = ' ';
      labyrinthe[(gy+oldgy)/2][(gx+oldgx)/2] = ' ';
    }
  }

  labyrinthe[0][1]                   = ' '; // entree
  labyrinthe[this.LAB_SIZE-2][this.LAB_SIZE-1] = ' '; // sortie

  for (int j=1; j<this.LAB_SIZE-1; j++) {
    for (int i=1; i<this.LAB_SIZE-1; i++) {
      if (labyrinthe[j][i]==' ') {
        if (labyrinthe[j-1][i]=='#' && labyrinthe[j+1][i]==' ' &&
          labyrinthe[j][i-1]=='#' && labyrinthe[j][i+1]=='#')
          sides[j-1][i][0] = 1;// c'est un bout de couloir vers le haut 
        if (labyrinthe[j-1][i]==' ' && labyrinthe[j+1][i]=='#' &&
          labyrinthe[j][i-1]=='#' && labyrinthe[j][i+1]=='#')
          sides[j+1][i][3] = 1;// c'est un bout de couloir vers le bas 
        if (labyrinthe[j-1][i]=='#' && labyrinthe[j+1][i]=='#' &&
          labyrinthe[j][i-1]==' ' && labyrinthe[j][i+1]=='#')
          sides[j][i+1][1] = 1;// c'est un bout de couloir vers la droite
        if (labyrinthe[j-1][i]=='#' && labyrinthe[j+1][i]=='#' &&
          labyrinthe[j][i-1]=='#' && labyrinthe[j][i+1]==' ')
          sides[j][i-1][2] = 1;// c'est un bout de couloir vers la gauche
      }
    }
  }

  // un affichage texte pour vous aider a visualiser le labyrinthe en 2D
  for (int j=0; j<this.LAB_SIZE; j++) {
    for (int i=0; i<this.LAB_SIZE; i++) {
      print(labyrinthe[j][i]);
      
    }
    // println("");
  }
   }

  public void toPShape(int sizeSide, String mode){this.toPShape(sizeSide, 2*sizeSide, mode);}
  public void toPShape(int sizeSide){this.toPShape(sizeSide, 2*sizeSide, "texture");}
  public void toPShape(int sizeW, int sizeH){this.toPShape(sizeW, sizeH, "texture");}
  public void toPShape(){this.toPShape(50, 100, "texture");}
  public void toPShape(String mode){this.toPShape(50, 100, mode);}



  public void toPShape(int sizeW, int sizeH, String mode){
    this.wallShape = createShape(GROUP);
    this.floorShape = createShape(GROUP);
    this.endEchelleShape = createechelle(20, sizeH*2, sizeW*0.4, color(0, 255, 0), color(0, 0, 255));
    this.couloirsShape = createShape(GROUP);
    this.treasureShape = createShape(GROUP);
    float texscale = 2f;
    for (int j=0; j<this.LAB_SIZE; j++) {
          for (int i=0; i<this.LAB_SIZE; i++) {
              pushMatrix();
              int typebout = -1;
              for(int k = 0; k < 4; k++){
                  if(this.sides[j][i][k] == 1){
                      typebout = k;
                  }
              }
              float r = map(i, 0, this.LAB_SIZE-1, 0, 255);
              float g = map(j, 0, this.LAB_SIZE-1, 0, 255);
              float b = map(this.LAB_SIZE-i, 0, this.LAB_SIZE-1, 0, 255);
              // if(tintFlag && dansLaby) tint(r,g,b);
              translate(i*sizeW, j*sizeW, 0);
              if (this.labyrinthe[j][i] == '#') {
                  PShape bloc = createShape(); 
                  bloc.beginShape(QUADS);
                  bloc.noStroke(); 
                  if(mode == "minimap"){
                      bloc.fill(r,g,b);
                      print(r, g, b);
                  }
                  else if(mode == "texture"){
                    push();
                    textureWrap(REPEAT);
                    bloc.texture(wall);
                    pop();
                  }
                  // fill(r,g,b);
                  if(j-1>=0 && this.labyrinthe[j-1][i] != '#'){
                      // if (typebout == 3) fill(255, 0, 0);
                      
                      bloc.vertex(0, 0, 0, 0, 0);
                      bloc.vertex(0,0,sizeH, 0, texscale);
                      bloc.vertex(sizeW, 0, sizeH, 1, texscale);
                      bloc.vertex(sizeW, 0, 0, 1, 0);
                  }
                  if(i-1>=0 && this.labyrinthe[j][i-1] != '#'){
                      // if (typebout == 1) fill(0, 0, 255);
                      bloc.vertex(0, 0, 0, 0, 0);
                      bloc.vertex(0, 0, sizeH, 0, texscale);
                      bloc.vertex(0, sizeW, sizeH, 1, texscale);
                      bloc.vertex(0, sizeW, 0, 1, 0);
                  }
                  // fill(r,g,b);
                  if(i+1<this.LAB_SIZE && this.labyrinthe[j][i+1] != '#'){
                      // if (typebout == 2) fill(255, 255, 0);
                      bloc.vertex(sizeW, sizeW, 0, 0, 0);
                      bloc.vertex(sizeW, sizeW, sizeH, 0, texscale);
                      bloc.vertex(sizeW, 0, sizeH, 1, texscale);
                      bloc.vertex(sizeW, 0, 0, 1, 0);
                  }
                  // fill(r,g,b);
                  if(j+1<this.LAB_SIZE && this.labyrinthe[j+1][i] != '#'){
                      // if (typebout == 0) fill(0, 255, 0);
                      bloc.vertex(0, sizeW, 0, 0, 0);
                      bloc.vertex(0, sizeW, sizeH, 0, texscale);
                      bloc.vertex(sizeW, sizeW, sizeH, 1, texscale); 
                      bloc.vertex(sizeW, sizeW, 0, 1, 0);
                  }
                  // fill(r,g,b);
                  bloc.endShape();
                  bloc.translate(i*sizeW, j*sizeW, 0);
                  wallShape.addChild(bloc);
              }else{
                  if(numetage == 0 || 
                  (
                    (numetage%2 == 0 && !(i == 1 && j == 0) ||
                    (numetage%2 == 1 && !(i == this.LAB_SIZE-1 && j == this.LAB_SIZE-2)))
                  )
                  ){
                    PShape sol = createShape(); 
                    sol.beginShape(QUADS);
                    sol.noStroke();
                    // sol.textureWrap(CLAMP);
                    sol.texture(floor);

                    sol.vertex(0, 0, 0, 0, 0);
                    sol.vertex(0,sizeW,0, 0, texscale);
                    sol.vertex(sizeW, sizeW, 0, 1, texscale);
                    sol.vertex(sizeW, 0, 0, 1, 0);
                    sol.endShape();
                    floorShape.addChild(sol);
                    sol.translate(i*sizeW, j*sizeW, 0);
                  }
                  // println("numetage: " + numetage + " pyramideHeight-1 : " + (pyramideHeight-1));
                  if(numetage == pyramideHeight-1 ||
                  (
                    (numetage%2 == 1 && !(i == 1 && j == 0) ||
                    (numetage%2 == 0 && !(i == this.LAB_SIZE-1 && j == this.LAB_SIZE-2)))
                  )
                  ){
                    PShape plafond = createShape(); 
                    plafond.beginShape(QUADS);
                    plafond.noStroke();
                    

                    plafond.texture(floor);
                    if(mode == "minimap"){plafond.tint(0, 0, 0, 150);}

                    plafond.vertex(0, 0, sizeH, 0, 0);
                    plafond.vertex(0,sizeW,sizeH, 0, texscale);
                    plafond.vertex(sizeW, sizeW, sizeH, 1, texscale);
                    plafond.vertex(sizeW, 0, sizeH, 1, 0);
                    plafond.endShape();
                    floorShape.addChild(plafond);
                    plafond.translate(i*sizeW, j*sizeW, 0);
                  }
                  if((numetage < pyramideHeight  && numetage%2 == 0 && (i == this.LAB_SIZE-1 && j == this.LAB_SIZE-2))){
                      PShape mur = createShape();
                      mur.translate(i*sizeW, j*sizeW, 0);
                      mur.beginShape(QUADS);
                      mur.texture(wall);
                      textureWrap(REPEAT);
                      mur.noStroke();
                      // mur.fill(255, 0, 0);
                      mur.vertex(sizeW, 0, 0, 0, 0);
                      mur.vertex(sizeW, sizeW, 0, 1, 0);
                      mur.vertex(sizeW,sizeW,sizeH*2, 1, 2*texscale);
                      mur.vertex(sizeW,0 ,sizeH*2, 0, 2*texscale);
                      
                      // mur.fill(0, 255, 0);
                      mur.vertex(0, 0, sizeH, 0, 0);
                      mur.vertex(sizeW, 0, sizeH, 1, 0);
                      mur.vertex(sizeW, 0, 2*sizeH, 1, texscale);
                      mur.vertex(0, 0, 2*sizeH, 0, texscale);

                      // mur.fill(0, 0, 255);
                      mur.vertex(0, sizeW, sizeH, 0, 0);
                      mur.vertex(sizeW, sizeW, sizeH, 1, 0);
                      mur.vertex(sizeW, sizeW, 2*sizeH, 1, texscale);
                      mur.vertex(0, sizeW, 2*sizeH, 0, texscale);

                      mur.endShape();
                      
                      couloirsShape.addChild(mur);
                      PShape plafond = createShape();
                      plafond.translate(i*sizeW, j*sizeW, 0);
                      plafond.beginShape(QUADS);
                      plafond.texture(floor);
                      textureWrap(CLAMP);
                      plafond.vertex(0, 0, 2*sizeH, 0, 0);
                      plafond.vertex(sizeW, 0, 2*sizeH, 1, 0);
                      plafond.vertex(sizeW, sizeW, 2*sizeH, 1, 1);
                      plafond.vertex(0, sizeW, 2*sizeH, 0, 1);
                      plafond.endShape();
                      couloirsShape.addChild(plafond);


                  }
                  if((numetage%2 == 1 && (i == this.LAB_SIZE-1 && j == this.LAB_SIZE-2))){
                      PShape mur = createShape();
                      mur.translate(i*sizeW, j*sizeW, 0);
                      mur.beginShape(QUADS);
                      mur.noStroke();
                      mur.texture(wall);
                      textureWrap(REPEAT);
                      // mur.fill(255, 0, 0);
                      mur.vertex(sizeW, 0, sizeH, 0, 0);
                      mur.vertex(sizeW, sizeW, sizeH, 1, 0);
                      mur.vertex(sizeW,sizeW, -sizeH, 1, 2*texscale);
                      mur.vertex(sizeW, 0 , -sizeH, 0, 2*texscale);
                      
                      // mur.fill(0, 255, 0);
                      mur.vertex(0, 0, 0, 0, 0);
                      mur.vertex(sizeW, 0, 0, 1, 0);
                      mur.vertex(sizeW, 0, -sizeH, 1, texscale);
                      mur.vertex(0, 0, -sizeH, 0, texscale);

                      // mur.fill(0, 0, 255);
                      mur.vertex(0, sizeW, 0, 0, 0);
                      mur.vertex(sizeW, sizeW, 0, 1, 0);
                      mur.vertex(sizeW, sizeW, -sizeH, 1, texscale);
                      mur.vertex(0, sizeW, -sizeH, 0, texscale);

                      mur.endShape();

                      couloirsShape.addChild(mur);

                      PShape sol = createShape();
                      sol.translate(i*sizeW, j*sizeW, 0);
                      sol.beginShape(QUADS);
                      sol.texture(floor);
                      textureWrap(CLAMP);
                      sol.vertex(0, 0, -sizeH, 0, 0);
                      sol.vertex(sizeW, 0, -sizeH, 1, 0);
                      sol.vertex(sizeW, sizeW, -sizeH, 1, 1);
                      sol.vertex(0, sizeW, -sizeH, 0, 1);
                      sol.endShape();
                      couloirsShape.addChild(sol);

                  }
                  if(numetage != 0 && numetage%2 == 0 && (i == 1 && j == 0)){
                    PShape mur = createShape();
                    mur.translate(i*sizeW, j*sizeW, 0);
                    mur.beginShape(QUADS);
                    mur.noStroke();
                    mur.texture(wall);
                    textureWrap(REPEAT);
                    // mur.fill(255, 0, 0);
                    mur.vertex(0, 0, sizeH, 0, 0);
                    mur.vertex(sizeW, 0, sizeH, 1, 0);
                    mur.vertex(sizeW, 0, -sizeH, 1, 2*texscale);
                    mur.vertex(0, 0 ,-sizeH, 0, 2*texscale);
                    
                    // mur.fill(0, 255, 0);
                    mur.vertex(0, 0, 0, 0, 0);
                    mur.vertex(0, sizeW,0, 1, 0);
                    mur.vertex(0, sizeW, -sizeH, 1, texscale);
                    mur.vertex(0, 0, -sizeH, 0, texscale);

                    // mur.fill(0, 0, 255);
                    mur.vertex(sizeW, 0, 0, 0, 0);
                    mur.vertex(sizeW, sizeW,0, 1, 0);
                    mur.vertex(sizeW, sizeW, -sizeH, 1, texscale);
                    mur.vertex(sizeW, 0, -sizeH, 0, texscale);

                    mur.endShape();

                    couloirsShape.addChild(mur);

                    PShape sol = createShape();
                    sol.translate(i*sizeW, j*sizeW, 0);
                    sol.beginShape(QUADS);
                    sol.texture(floor);
                    textureWrap(CLAMP);
                    sol.vertex(0, 0, -sizeH, 0, 0);
                    sol.vertex(sizeW, 0, -sizeH, 1, 0);
                    sol.vertex(sizeW, sizeW, -sizeH, 1, 1);
                    sol.vertex(0, sizeW, -sizeH, 0, 1);
                    sol.endShape();
                    couloirsShape.addChild(sol);

                    
                  }
                  if(numetage < pyramideHeight  && numetage%2 == 1 && (i == 1 && j == 0)){
                    PShape mur = createShape();
                    mur.translate(i*sizeW, j*sizeW, 0);
                    mur.beginShape(QUADS);
                    mur.noStroke();
                    mur.texture(wall);
                    textureWrap(REPEAT);
                    // mur.fill(255, 0, 0);
                    mur.vertex(0, 0, 0, 0, 0);
                    mur.vertex(sizeW, 0, 0, 1, 0);
                    mur.vertex(sizeW, 0, 2*sizeH, 1, 2*texscale);
                    mur.vertex(0, 0 ,2*sizeH, 0, 2*texscale);
                    
                    // mur.fill(0, 255, 0);
                    mur.vertex(0, 0, sizeH, 0, 0);
                    mur.vertex(0, sizeW,sizeH, 1, 0);
                    mur.vertex(0, sizeW, 2*sizeH, 1, texscale);
                    mur.vertex(0, 0, 2*sizeH, 0, texscale);

                    // mur.fill(0, 0, 255);
                    mur.vertex(sizeW, 0, sizeH, 0, 0);
                    mur.vertex(sizeW, sizeW,sizeH, 1, 0);
                    mur.vertex(sizeW, sizeW, 2*sizeH, 1, texscale);
                    mur.vertex(sizeW, 0, 2*sizeH, 0, texscale);

                    mur.endShape();

                    couloirsShape.addChild(mur);

                    PShape plafond = createShape();
                    plafond.translate(i*sizeW, j*sizeW, 0);
                    plafond.beginShape(QUADS);
                    plafond.texture(floor);
                    textureWrap(CLAMP);
                    plafond.vertex(0, 0, 2*sizeH, 0, 0);
                    plafond.vertex(sizeW, 0, 2*sizeH, 1, 0);
                    plafond.vertex(sizeW, sizeW, 2*sizeH, 1, 1);
                    plafond.vertex(0, sizeW, 2*sizeH, 0, 1);
                    plafond.endShape();
                    couloirsShape.addChild(plafond);
                  }
                  if(numetage == 0 && i == 1 && j == 0){
                    PShape solSortie = createShape();
                    solSortie.translate(i*sizeW, j*sizeW, 0);
                    solSortie.beginShape(QUADS);
                    solSortie.texture(floor);
                    solSortie.noStroke();
                    textureWrap(CLAMP);
                    solSortie.vertex(0, 0, 0, 0, 0);
                    solSortie.vertex(sizeW, 0, 0, 1, 0);
                    solSortie.vertex(sizeW, -sizeW, 0, 1, 1);
                    solSortie.vertex(0, -sizeW, 0, 0, 1);
                    solSortie.endShape();
                    floorShape.addChild(solSortie);
                    
                    for(int k = 0; k < 2; k++){
                    PShape sortie = createShape();
                    sortie.translate(i*sizeW, j*sizeW, 0);
                    sortie.beginShape();
                    sortie.noStroke();
                    sortie.texture(wall);
                    textureWrap(REPEAT);
                    // sortie.fill(255, 0, 0);
                    float marcheWidth = (float)sizeW/(nbMarche);
                    float marcheHeight = (float)sizeH/(nbMarche);
                      sortie.vertex(k*sizeW, 0, 0, 0, 0);
                      sortie.vertex(k*sizeW, -sizeW, 0, 1, 0);

                        for(int m = 0; m < nbMarche; m++){
                          sortie.vertex(k*sizeW, -sizeW+marcheWidth*(m), (m+1)*marcheHeight, 1.0 - (float)(m)/nbMarche, texscale*(m+1)/(nbMarche));
                          sortie.vertex(k*sizeW, -sizeW+marcheWidth*(m+1), (m+1)*marcheHeight, 1.0 - (float)(m+1)/nbMarche, texscale*(m+1)/(nbMarche));
                        }
                        sortie.vertex(k*sizeW, 0, sizeH, 0, texscale*(nbMarche)/(nbMarche));
                    sortie.endShape(CLOSE);
                    wallShape.addChild(sortie);
                    }

                  }
                  if(numetage == pyramideHeight-1){
                    if(numetage%2 == 0 && (i == this.LAB_SIZE-1 && j == this.LAB_SIZE-2)){
                      println("je me suis shape chest PAIR");
                      chest.rotateZ(-PI/2);
                      chest.translate(i*sizeW+25, j*sizeW+25, 0);
                      treasureShape.addChild(chest);

                    }
                    if(numetage%2 == 1 && (i == 1 && j == 0)){
                      println("je me suis shape chest IMPAIR");
                      chest.rotateZ(PI);
                      chest.translate(i*sizeW+25, j*sizeW+25, 0);
                      treasureShape.addChild(chest);
                    }
                  }


              }

              popMatrix();
          }
      }
      // if(mode == "texture"){
        if(numetage == 0){
          this.startEchelleShape = createShape(GROUP);
        }else{
          this.startEchelleShape = createechelle(20, sizeH*2, sizeW*0.4, color(0, 255, 0), color(0, 0, 255));
        }
        if(numetage == pyramideHeight-1){
          this.endEchelleShape = createShape(GROUP);
          }
        float wallOffset = 2;
        if(numetage%2 == 0 ){
          //en bas à droite du laby
          // println("pair ma gueule");

          endEchelleShape.rotateZ(PI/2);
          endEchelleShape.translate((this.LAB_SIZE)*sizeW-wallOffset, (this.LAB_SIZE-1)*sizeW-sizeW/2.0, sizeH);
          startEchelleShape.translate(sizeW+sizeW/2.0, wallOffset, 0);
        }else{
          //en haut à gauche du laby
          // println("impair ma gueule");
          endEchelleShape.translate(sizeW+sizeW/2.0, wallOffset, sizeH);
          startEchelleShape.rotateZ(PI/2);
          startEchelleShape.translate((this.LAB_SIZE)*sizeW-wallOffset, (this.LAB_SIZE-1)*sizeW-sizeW/2.0, 0);
        }
      // }
      return;
}




  

  public void visite(int a, int b){
    for(int x = -1; x < 2; x++){
      for(int y = -1; y < 2; y++){
          if(a+y >= 0 && a+y < this.LAB_SIZE && b+x >= 0 && b+x < this.LAB_SIZE){
            visited[b+x][a+y] = true;
          }
        }
      }
  }
  public void visiteAll(){
     for (int i = 0; i < this.LAB_SIZE; i++) {
      for (int j = 0; j < this.LAB_SIZE; j++) {
        visited[i][j] = true;
      }
    }
  }

}