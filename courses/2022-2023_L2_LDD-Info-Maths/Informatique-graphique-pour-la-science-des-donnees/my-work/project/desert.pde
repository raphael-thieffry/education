/*  void setup(){
   size(1000,1000,P3D);
 }
 void draw(){
   camera(1000*cos(PI/100.0), 1000*sin(PI/100.0),-75, 
          0,0,0,
          0,0,1);
   background(135,206,235);
    
     noLoop();
   img.updatePixels();
   for(int j=-300; j<300; j++){
     for(int i=-300; i<300; i++){
     noStroke();
  
     beginShape(QUADS);
     texture(img);
       fill(0,0,0);
       //fill(255, 205+50*noise(i/1.0,j/1.0), 0);
       vertex(i*5,    j*5,    150*noise(i/50.0,j/50.0), (i+300)/6,(j+300)/6);
       vertex((i+1)*5,j*5,    150*noise((i+1)/50.0,j/50.0), (i+300)/6,(j+300)/6);
       vertex((i+1)*5,(j+1)*5,150*noise((i+1)/50.0,(j+1)/50.0), (i+300)/6,(j+300)/6);
       vertex(i*5,    (j+1)*5,150*noise((i+0)/50.0,(j+1)/50.0), (i+300)/6,(j+300)/6);
       endShape();
     }
   }
 } */