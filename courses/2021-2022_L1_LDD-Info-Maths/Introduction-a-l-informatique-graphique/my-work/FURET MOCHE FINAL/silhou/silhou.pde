PImage img, img2;
PGraphics img3;

int col = color(255,0,0);
int selpix = 0;
int iniMouseX, iniMouseY;
float minr, maxr, ming, maxg, minb, maxb;
float minh, maxh, mins, maxs, minbr, maxbr;
int minx, miny, maxx, maxy;
int minx0, miny0, maxx0, maxy0;
ArrayList<PVector> lastMousePoints = new ArrayList<PVector>();
boolean alt = false;
int BUTTON_LEFT  = 37;
int BUTTON_RIGHT = 39;
int MOUSE_STATE  = 0;

void setup() {
    
    size(820,761);
    
    //l'image de depart
    img = loadImage("skunk.png");
    img.loadPixels();
    
    //pour dessiner la zone selectionnee
    img2 = createImage(img.width, img.height, ARGB);
    img2.loadPixels();
    
    //pour dessiner les poils
    img3 = createGraphics(img.width, img.height);
    
    pixelDensity(displayDensity());
    background(255);
    frameRate(15);
}


void draw() {
    background(255);
    noTint();
    image(img,0,0);
    
    //etape 2.3
    //ici on peut jouer sur la teinture de l'image pour faire une
    //animation moins binaire
    if (frameCount % 5 ==  0) {
        tint(255, 100);
    }else{
        tint(255, 200);
    }
    image(img2,0,0); 
    noTint();
    image(img3,0,0);
}

// pour les macs
void keyPressed() {
    if (key == CODED && keyCode == ALT) alt = true;
}

void keyReleased() {
    if (key == CODED && keyCode == ALT) alt = false;
}


void mousePressed() {
    MOUSE_STATE = mouseButton;
    println(mouseButton);
    if (mouseButton == BUTTON_LEFT) {
        // si on commence un drag & drop avec le bouton gauche, on selectionne 
        iniMouseX = -1;
        lastMousePoints.clear();
        col = img.pixels[mouseX + mouseY * img.width];
        
        // on recommence toute la selection  donc on remet a zero toutes les variables
        // qui concernent les stats de la selection
        maxr  = red(col);
        minr  = red(col);
        maxg  = green(col);
        ming  = green(col);
        maxb  = green(col);
        minb  = blue(col);
        minh  = hue(col);
        maxh  = hue(col);
        mins  = saturation(col);
        minx  = mouseX;
        maxx  = mouseX;
        miny  = mouseX;
        maxy  = mouseY;
        minx0 = mouseX;
        maxx0 = mouseX;
        miny0 = mouseX;
        maxy0 = mouseY;
        
        selpix = 1;
        // on recommence toute la selection donc on remet tous les pixels transparents
        for (int j = 0; j < img.height; j++)
            for (int i = 0; i < img.width; i++) {
                img2.pixels[i + j * img2.width] = color(0,0,0, 0);
            }
        img2.pixels[mouseX + mouseY * img2.width] = color(0,0,0);
    } else if (mouseButton == BUTTON_RIGHT || (mouseButton == BUTTON_LEFT && alt)) {
        // si on commence un drag & drop avec le bouton droit (ou avec la touche alt pour les macs)
        iniMouseX = mouseX;
        iniMouseY = mouseY;
        
    }
}

void mouseDragged() {
    if (MOUSE_STATE == BUTTON_LEFT) {
        // on rajoute un point de drag&drop dans la selection
        col = img.pixels[mouseX + mouseY * img.width];
        maxr = minr = red(col);
        maxg = ming = green(col);
        maxb = minb = blue(col);
        minh = hue(col);
        maxh = hue(col);
        mins = saturation(col);
        minx = maxx = mouseX;
        miny = maxy = mouseY;
        
        // on ne garde en memoire que les 25 derniers points pour pas trop 
        // rajouter de travail
        if (lastMousePoints.size()>25) {
            lastMousePoints.remove(lastMousePoints.size() - 1);
        }
        lastMousePoints.add(0, new PVector(mouseX, mouseY, col));
        
        // pour les 25 derniers points on met a jour les stats
        for (PVector v : lastMousePoints) {
            int x0 = int(v.x);
            int y0 = int(v.y);
            col    = img.pixels[x0 + y0 * img.width];
            minr   = min(minr, red(col));
            maxr   = max(maxr, red(col));
            ming   = min(ming, green(col));
            maxg   = max(maxg, green(col));
            minb   = min(minb, blue(col));
            maxb   = max(maxb, blue(col));
             
            minh   = min(minh, hue(col));
            maxh   = max(maxh, hue(col));
            mins   = min(mins, saturation(col));
            maxs   = max(maxs, saturation(col));
            minbr  = min(minbr, brightness(col));
            maxbr  = max(maxbr, brightness(col));
             
            minx   = min(minx, x0);
            maxx   = max(maxx, x0);
            miny   = min(miny, y0);
            maxy   = max(maxy, y0);
        } 
        
        // en fonction des stats on selectionne tous les points autour qui
        // ressemblent (memes couleurs)
        int iniselpix = selpix - 1;
        while(iniselpix!= selpix) {
            // on recommence en boucle tant que ca rajoute des points
            iniselpix = selpix;
            selpix = 0;
            for (int j = max(0, miny - 1); j <= min(maxy + 1,img.height - 1); j++) {
                for (int i = max(0, minx - 1); i <= min(maxx + 1,img.width - 1); i++) {
                    int     p    = img.pixels[i + j * img.width];
                    boolean tsel = j > miny - 1 && j > 0              && alpha(img2.pixels[i + (j - 1) * img2.width]) > 128;
                    boolean bsel = j < maxy + 1 && j < img.height - 1 && alpha(img2.pixels[i + (j + 1) * img2.width]) > 128;
                    boolean lsel = i > minx - 1 && i > 0              && alpha(img2.pixels[(i - 1) + j * img2.width]) > 128;
                    boolean rsel = i < maxx + 1 && i < img.width - 1  && alpha(img2.pixels[(i + 1) + j * img2.width]) > 128;
                    
                    float avgr   = (minr + maxr) / 2;
                    float gapr   = (maxr - minr) / 2;
                    float avgg   = (ming + maxg) / 2;
                    float gapg   = (maxg - ming) / 2;
                    float avgb   = (minb + maxb) / 2;
                    float gapb   = (maxb - minb) / 2;
                     
                    float avgh   = (minh  + maxh )   / 2;
                    float gaph   = (maxh  - minh )   / 2;
                    float avgs   = (mins  + maxs )   / 2;
                    float gaps   = (maxs  - mins )   / 2;
                    float avgbr  = (minbr + maxbr) / 2;
                    float gapbr  = (maxbr - minbr) / 2;
                    
                    float tol = 1.0 + ((tsel ? 0.05 : 0) + (bsel ? 0.05 : 0) + (lsel ? 0.05 : 0) + (rsel ? 0.05 : 0));
                    if ( 
                                  red(p) >= avgr  - gapr  * tol 
                        &&        red(p) <= avgr  + gapr  * tol 
                        &&      green(p) >= avgg  - gapg  * tol 
                        &&      green(p) <= avgg  + gapg  * tol 
                        &&       blue(p) >= avgb  - gapb  * tol 
                        &&       blue(p) <= avgb  + gapb  * tol 
                        &&        hue(p) >= avgh  - gaph  * tol 
                        &&        hue(p) <= avgh  + gaph  * tol 
                        && saturation(p) >= avgs  - gaps  * tol 
                        && saturation(p) <= avgs  + gaps  * tol 
                        && brightness(p) >= avgbr - gapbr * tol 
                        && brightness(p) <= avgbr + gapbr * tol 
                        && (tsel || bsel || lsel || rsel)
                       ) {
                        img2.pixels[i + j * img2.width] = color(255,0,0); //etape2.1
                        selpix++;
                        minx  = min(minx , i);
                        maxx  = max(maxx , i);
                        miny  = min(miny , j);
                        maxy  = max(maxy , j);
                        minx0 = min(minx0, i);
                        maxx0 = max(maxx0, i);
                        miny0 = min(miny0, j);
                        maxy0 = max(maxy0, j);            
                    }
                }  
            }
        }
        
        //etape2.2
        // ici on peut bidouiller les couleurs des pixels selectionnes
        // en fonction de leur position ou de leur voisin
        colorMode(HSB, 255) ;
        for (int j = 1; j < img2.height - 1; j++) {
            for (int i = 1; i < img2.width - 1; i++) {
                if (alpha(img2.pixels[i + j * img2.width])>128){
                        float rselec = 255-red(img.pixels[i + j * img2.width]);
                        float bselec = 255-blue(img.pixels[i + j * img2.width]);
                        float gselec = 255-green(img.pixels[i + j * img2.width]);
                        int colordupixel = color(rselec,gselec,bselec, 255);

                        colordupixel = color(hue(colordupixel),saturation(int((saturation(colordupixel))+255)/2),brightness(colordupixel));
                    img2.pixels[i + j * img2.width] = colordupixel;
                    
                }
            }
        }
        colorMode(RGB,255);
        img2.updatePixels();
        
    }
}
void mouseReleased() {
    img3.beginDraw();
    float endMouseX;
    float endMouseY;
    MOUSE_STATE = 0;
    if (iniMouseX >=  0) {
        endMouseX = mouseX;
        endMouseY = mouseY;
        float directionX = (endMouseX-iniMouseX)/dist(endMouseX,endMouseY,iniMouseX,iniMouseY);
        float directionY = (endMouseY-iniMouseY)/dist(endMouseX,endMouseY,iniMouseX,iniMouseY);
        float orthoX = -directionY;
        float orthoY = directionX;
        int nombreSeg = int(dist(endMouseX,endMouseY,iniMouseX,iniMouseY)/6); //on compte les pixels qui nous separent du point de depart, et on dit des segments, j'en veux 6 fois moins que cette distance
        float longueurPoil = dist(endMouseX,endMouseY,iniMouseX,iniMouseY)/nombreSeg;
        float segmentX=0;
        float segmentY=0;
        float departX = iniMouseX;
        float departY = iniMouseY;
        float puisOrth = random(-1,1);
        int colorDepart;
        //float oldPuis = puisOrth;
        //float moyGlob = puisOrth;
        //int change = 1;
        int nombrePoils = (maxx0-minx0)*(maxy0-miny0)/(100/3); //3% des pixels en moyenne seront des points de depart pour faire simple
       // img.loadPixels();
        ArrayList<PVector> listeDeparts = new ArrayList<PVector>();
        int counter = 0;
        while(counter < nombrePoils){
          float randXZone = random(minx0,maxx0);
          float randYZone = random(miny0,maxy0);
          if(alpha(img2.pixels[int(randXZone + randYZone * img2.width)]) > 100){
              PVector randZone = new PVector(randXZone,randYZone);
              listeDeparts.add(randZone);
              counter+=1;
          }

        }
        stroke(0.5);
        for(PVector d : listeDeparts){
            departX = d.x ;
            departY = d.y ;
            //dessine un poil
            int pixelDepart = img.pixels[int(d.x) + int(d.y) * img.width];
            //int tendance = round(random(0,1));
            for(int i = 0; i<nombreSeg;i++){
                if(i!= 0){
                  departX = segmentX;
                  departY = segmentY;              
                }
                puisOrth = random(-1,1);
                /*float probaChangement[] = {-0.75,1};
                change=1;
                if(round(random(0,100)) <= 10){
                  change=0;
                }else{
                  oldPuis = puisOrth;
                }
                puisOrth = oldPuis*probaChangement[change];
                moyGlob = (oldPuis+puisOrth)/2;*/
                segmentX = departX+longueurPoil*directionX+orthoX*(puisOrth*i/nombreSeg)*10;
                segmentY = departY+longueurPoil*directionY+orthoY*(puisOrth*i/nombreSeg)*10;
                colorDepart = color(red(pixelDepart),green(pixelDepart),blue(pixelDepart));
                colorMode(HSB, 255);
                colorDepart = color(hue(pixelDepart), saturation(pixelDepart), 255*(i/nombreSeg)); //revoir brightness segment
                img3.stroke(colorDepart);
                colorMode(RGB, 255);
                img3.strokeWeight((1-(i/nombreSeg)*1)*1.2);
                img3.line(departX,departY,segmentX,segmentY); 
            }
        }
        //couleur avec img.pixels etc....

      img3.endDraw();
    }
}
