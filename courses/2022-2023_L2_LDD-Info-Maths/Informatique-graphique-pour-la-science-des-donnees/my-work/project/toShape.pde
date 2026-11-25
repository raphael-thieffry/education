PShape labyToMinimap(Labyrinthe laby, int sizeC){
  PShape shape0 = createShape(GROUP);     //composé de
  for (int j=0; j<laby.LAB_SIZE; j++) {
        for (int i=0; i<laby.LAB_SIZE; i++) {
          if(!laby.visited[j][i]) continue;
            pushMatrix();

            float r = map(i, 0, laby.LAB_SIZE-1, 0, 255);
            float g = map(j, 0, laby.LAB_SIZE-1, 0, 255);
            float b = map(laby.LAB_SIZE-i, 0, laby.LAB_SIZE-1, 0, 255);
            
            translate(i*sizeC, j*sizeC, 0);
            if (laby.labyrinthe[j][i] == '#') {
                PShape bloc = createShape();  
                bloc.beginShape(QUADS);
                bloc.fill(r,g,b);
                bloc.noStroke();
                // fill(r,g,b);
                if(j-1>=0 && laby.labyrinthe[j-1][i] != '#'){
                    // if (typebout == 3) fill(255, 0, 0);
                    
                    bloc.vertex(0, 0, 0, 0, 0);
                    bloc.vertex(0,0,sizeC, 0, 1);
                    bloc.vertex(sizeC, 0, sizeC, 1, 1);
                    bloc.vertex(sizeC, 0, 0, 1, 0);
                }
                if(i-1>=0 && laby.labyrinthe[j][i-1] != '#'){
                    // if (typebout == 1) fill(0, 0, 255);
                    bloc.vertex(0, 0, 0, 0, 0);
                    bloc.vertex(0, 0, sizeC, 0, 1);
                    bloc.vertex(0, sizeC, sizeC, 1, 1);
                    bloc.vertex(0, sizeC, 0, 1, 0);
                }
                // fill(r,g,b);
                if(i+1<laby.LAB_SIZE  && laby.labyrinthe[j][i+1] != '#'){
                    // if (typebout == 2) fill(255, 255, 0);
                    bloc.vertex(sizeC, sizeC, 0, 0, 0);
                    bloc.vertex(sizeC, sizeC, sizeC, 0, 1);
                    bloc.vertex(sizeC, 0, sizeC, 1, 1);
                    bloc.vertex(sizeC, 0, 0, 1, 0);
                }
                // fill(r,g,b);
                if(j+1<laby.LAB_SIZE && laby.labyrinthe[j+1][i] != '#'){
                    // if (typebout == 0) fill(0, 255, 0);
                    bloc.vertex(0, sizeC, 0, 0, 0);
                    bloc.vertex(0, sizeC, sizeC, 0, 1);
                    bloc.vertex(sizeC, sizeC, sizeC, 1, 1); 
                    bloc.vertex(sizeC, sizeC, 0, 1, 0);
                } 
                // fill(r,g,b);
                bloc.endShape();
                bloc.translate(i*sizeC, j*sizeC, 0);
                shape0.addChild(bloc);
            }else{
                PShape sol = createShape(); 
                sol.beginShape(QUADS);
                sol.noStroke();
                // sol.strokeWeight(0.5);
                // sol.stroke(255);
                // sol.texture(floor);
                sol.fill(r,g,b);
                sol.vertex(0, 0, 0, 0, 0);
                sol.vertex(0,sizeC,0, 0, 1);
                sol.vertex(sizeC, sizeC, 0, 1, 1);
                sol.vertex(sizeC, 0, 0, 1, 0);
                sol.endShape();
                shape0.addChild(sol);
                sol.translate(i*sizeC, j*sizeC, 0);

            }
            popMatrix();
        }
  }
  return shape0;
}





// sphere (pour les yeux)
public PShape createSphere(color c){
        PShape sphereShape = createShape();
        sphereShape.beginShape(QUAD_STRIP);
        sphereShape.ambient(255);
        sphereShape.specular(255);
        sphereShape.shininess(255);
        sphereShape.emissive(c/2.);
        sphereShape.fill(c);
        sphereShape.noStroke();
        for (int i = 0; i <= 180; i += 10) {
            for (int j = 0; j <= 360; j += 10) {
            // Calcule les coordonnées sphériques de chaque point
            float x = sin(radians(i)) * cos(radians(j)) * 10;
            float y = sin(radians(i)) * sin(radians(j)) * 10;
            float z = cos(radians(i)) * 10;
            float nx = x / 10;
            float ny = y / 10;
            float nz = z / 10;
            sphereShape.normal(nx, ny, nz);
            sphereShape.vertex(x, y, z);
            
            // Calcule les coordonnées sphériques du point suivant sur le même cercle de latitude
            float x2 = sin(radians(i+10)) * cos(radians(j)) * 10;
            float y2 = sin(radians(i+10)) * sin(radians(j)) * 10;
            float z2 = cos(radians(i+10)) * 10;
            float nx2 = x2 / 10;
            float ny2 = y2 / 10;
            float nz2 = z2 / 10;
            sphereShape.normal(nx2, ny2, nz2);
            sphereShape.vertex(x2, y2, z2);
            
            // Calcule les coordonnées sphériques des normales pour chaque point
            
            }
            // Ajoute le premier point de la bande à la bande suivante pour former un quad
            float x3 = sin(radians(i)) * cos(radians(0)) * 10;
            float y3 = sin(radians(i)) * sin(radians(0)) * 10;
            float z3 = cos(radians(i)) * 10;
            float nx3 = x3 / 10;
            float ny3 = y3 / 10;
            float nz3 = z3 / 10;
            sphereShape.normal(nx3, ny3, nz3);
            sphereShape.vertex(x3, y3, z3);
            float x4 = sin(radians(i+10)) * cos(radians(0)) * 10;
            float y4 = sin(radians(i+10)) * sin(radians(0)) * 10;
            float z4 = cos(radians(i+10)) * 10;
            float nx4 = x4 / 10;
            float ny4 = y4 / 10;
            float nz4 = z4 / 10;
            sphereShape.normal(nx4, ny4, nz4);
            sphereShape.vertex(x4, y4, z4);
            
            // Calcule les coordonnées sphériques des normales pour les points de la bande suivante
            
        }
        sphereShape.endShape();
        return sphereShape;
    }

// echelle

PShape createCylinder(float radius, float height, int detail, color c) {
  PShape cylinder = createShape();
  cylinder.beginShape(QUAD_STRIP);
  cylinder.noStroke();
  cylinder.fill(c);
  for (int i = 0; i <= detail; i++) {
    float angle = TWO_PI / detail * i;
    float x = cos(angle);
    float z = sin(angle); //z c'est y en fait
    PVector n = (new PVector(-x, -z, 0)).normalize();
    cylinder.normal(n.x, n.y, n.z);
    cylinder.texture(wood);
    textureWrap(REPEAT);
    cylinder.vertex(x * radius,z * radius, -height/2, i, 0);
    cylinder.vertex(x * radius, z * radius, height/2, i, 1);
  }
  cylinder.endShape();
  return cylinder;
}

PShape createechelle(int nbBarreau, float hauteur, float largeur, color colorBarreau, color trucSurLeCote){
    PShape echelle = createShape(GROUP);
    for(int i = 0; i < nbBarreau; i++){
        PShape barreau = createCylinder(largeur/15, largeur*0.9, 20, colorBarreau);
        barreau.rotateX(PI/2);
        barreau.rotateZ(PI/2);
        barreau.translate(0, 0, hauteur/(2*nbBarreau) + i*hauteur/nbBarreau - hauteur/2);
        echelle.addChild(barreau);
    }
    PShape truc1 = createCylinder(1.2*largeur/15, hauteur, 20, trucSurLeCote);
    truc1.translate(-largeur/2, 0, 0);
    echelle.addChild(truc1);
    PShape truc2 = createCylinder(1.2*largeur/15, hauteur, 20, trucSurLeCote);
    truc2.translate(largeur/2, 0, 0);
    echelle.addChild(truc2);
    
    return echelle;
}

PShape createFloorDesert(int detail, float amplitude, float frequence){
    int nbCasesLargeur = (limiteSupMonde - limiteInfMonde);
    int nbPolygonesLargeur = nbCasesLargeur*(detail);

    PShape floor = createShape();
    floor.translate(0,0, -amplitude*0.75);
    floor.beginShape(QUADS);
    for(int j=limiteInfMonde*detail; j<limiteSupMonde*detail; j++){
     for(int i=limiteInfMonde*detail; i<limiteSupMonde*detail; i++){
            float reali = float(i)/float(detail);
            float realj = float(j)/float(detail);
            float reali1 = float(i+1)/float(detail);
            float realj1 = float(j+1)/float(detail);
            float currentamplitude = amplitude;
            float nbRepet = 1; //ne fonctionne pas
            textureWrap(REPEAT);
            floor.noStroke();
            floor.texture(sand);
            floor.fill(0,0,0);
            floor.vertex(reali*50,    realj*50,    amplitude*noise(reali*frequence,realj*frequence), 
                                                   nbRepet * (reali+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur), 
                                                   nbRepet * (realj+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur));
            floor.vertex(reali1*50,   realj*50,    amplitude*noise(reali1*frequence,realj*frequence), 
                                                   nbRepet * (reali1+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur), 
                                                   nbRepet * (realj+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur));
                                                    
            floor.vertex(reali1*50,   realj1*50,   amplitude*noise(reali1*frequence,realj1*frequence), 
                                                   nbRepet * (reali1+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur), 
                                                   nbRepet * (realj1+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur));
                                                   
            floor.vertex(reali*50,    realj1*50,   amplitude*noise(reali*frequence,realj1*frequence), 
                                                   nbRepet * (reali+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur), 
                                                   nbRepet * (realj1+nbPolygonesLargeur/2.)/float(nbPolygonesLargeur));
                                                   
     }
   }
   floor.endShape();
   return floor;
}