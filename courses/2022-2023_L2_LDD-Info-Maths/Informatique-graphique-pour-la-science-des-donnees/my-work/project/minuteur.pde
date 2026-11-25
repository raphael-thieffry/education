


public class Minuteur{
    private int seconde;
    private int minute;
    private int old_sec = millis();
    PGraphics text = createGraphics(width,height,P2D);
    // private int sec = millis();
    public Minuteur(int sec){
        seconde = sec%60;
        minute = sec/60;
        toTexte();
    }
    public void affiche(){
        System.out.println(minute+"min"+seconde+"sec");
    }
    public void incremente(){
        seconde++;
        if(seconde==60){
            seconde=0;
            minute++;
        }
    }
    public void decremente(){
        seconde--;
        if(seconde==-1){
            seconde=59;
            minute--;
        }
    }
    public void reset(){
        seconde=0;
        minute=0;
    }
    public void set(int sec){
        seconde = sec%60;
        minute = sec/60;
    }
    public int get(){
        return minute*60+seconde;
    }
    public void add(int sec){
        seconde+=sec;
        minute+=seconde/60;
        seconde%=60;
    }
    public void sub(int sec){
        seconde-=sec;
        minute+=seconde/60;
        seconde%=60;
    }
    public boolean isNull(){
        return seconde==0 && minute==0;
    }
    public void toTexte(){

        text.beginDraw();
        text.clear();
        
        // text.textSize(32);
        text.fill(255);
        // text.background(255, 0, 0);
        text.textAlign(CENTER);
        text.textFont(createFont("Arial", 22));
        if(minute<10){
            if(seconde<10)
                text.text("0"+minute+":0"+seconde,width/2, height/2+text.textAscent()/2);
            else
                text.text("0"+minute+":"+seconde,width/2, height/2+text.textAscent()/2);
        }
        else{
            if(seconde<10)
                text.text(minute+":0"+seconde,width/2, height/2+text.textAscent()/2);
            else
                text.text(minute+":"+seconde,width/2, height/2+text.textAscent()/2);

        }
        text.endDraw();
    }
    public void update(){
        if(millis()-old_sec>1000){
            println("je mes à jours le minuteur");
            old_sec=millis();
            if(!isNull()){
                decremente();
            }
            this.toTexte();
        }
    }
    public void log(){
        if(minute<10){
            if(seconde<10)
                System.out.println("0"+minute+":0"+seconde);
            else
                System.out.println("0"+minute+":"+seconde);
        }
        else{
            if(seconde<10)
                System.out.println(minute+":0"+seconde);
            else
                System.out.println(minute+":"+seconde);
        }
    }


}