package flappyBird;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.Random;
import javafx.scene.image.Image;
import javax.swing.JFrame;
import javax.swing.Timer;
//import java.awt.Image;
import javafx.scene.paint.ImagePattern;
import javax.swing.ImageIcon;

public final class flappyBird implements ActionListener, KeyListener{                           //Erstellt Gamescreen
    
    public static flappyBird flappybird;
    public final int WIDTH = 800, HEIGHT = 800;
    public Renderer renderer;
    public Rectangle bird;
    public int ticks, ymotion, score;
    public boolean gameover, started;
    public ArrayList<Rectangle> columns;
    public Random rand;
    
    public flappyBird(){
        JFrame jframe = new JFrame();
        Timer timer = new Timer(20, this);
        renderer = new Renderer();      //gegen NullPointerException!!
        rand = new Random();
        
        jframe.add(renderer);
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.setSize(WIDTH,HEIGHT);
        jframe.addKeyListener(this);
        jframe.setResizable(false);
        jframe.setTitle("Flappy Bird");
        jframe.setVisible(true);
        
        bird = new Rectangle(WIDTH / 2-10, HEIGHT/2-10, 20, 20);
        columns = new ArrayList<>();
        
        addColumn(true);
        addColumn(true);
        addColumn(true);
        addColumn(true);
        
        timer.start();                          //notwendig damit alle 20 milisekunden das repaint ausgeführt wird!
    }
  
    public void addColumn(boolean start){                    //Hier werden die neuen grünen Säulen hinzugefügt                  
        int space= 300;
        int width= 100; 
        int height = 50 + rand.nextInt(300);
        
        if(start){
        //die Untere
        columns.add(new Rectangle(WIDTH +width +columns.size()* 300, HEIGHT - height - 150, width , height));
        //die Obere
        columns.add(new Rectangle(WIDTH + width + (columns.size()-1) *300, 0, width, HEIGHT- height -space));
        } else{
            columns.add(new Rectangle(columns.get(columns.size()-1).x+600,HEIGHT - height - 150, width , height));
            columns.add(new Rectangle(columns.get(columns.size()-1).x, 0, width, HEIGHT- height -space));
        }
    }
    
    public void paintColumn(Graphics g, Rectangle column){
        g.setColor(Color.green.darker());
        g.fillRect(column.x, column.y, column.width, column.height);
    }
    
    public void jump(){
        if(gameover){
            bird = new Rectangle(WIDTH / 2-10, HEIGHT/2-10, 20, 20);
            columns.clear();
            ymotion = 0;
            score = 0;
        
            addColumn(true);
            addColumn(true);
            addColumn(true);
            addColumn(true);
            started = true;
            gameover = false;
        }
        if(!started){
            started = true;
        }else if(!gameover){
            if(ymotion >0){
                ymotion = 0;
            }ymotion -=10;
        }
    }
    
     @Override
    public void actionPerformed(ActionEvent e) {
        int speed = 10;                                 //für schnelligkeit des bewegenden screens!!
        ticks++;
        
        if(started){
        for(int i = 0; i < columns.size(); i++){        //für Bewegung des Screens
            Rectangle column = columns.get(i);
            column.x -= speed;
        }
        if(ticks%2 == 0 && ymotion<15){
            ymotion +=2;
        }
        
         for(int i = 0; i < columns.size(); i++){       //2. Forschleife für die endlose erscheinung von Columns
            Rectangle column = columns.get(i);
            if(column.x + column.width <0){
                columns.remove(column);
                if(column.y ==0){
                    addColumn(false);
                }
            }
        }
        
        bird.y += ymotion;
        
        for(Rectangle column : columns){     
            
            //Score , equals 0 weil es 2 säulen sind, sonst hätte man pro säule +2 im score!!
            if(!gameover){
            if(column.y == 0 &&bird.x + bird.width /2 > column.x + column.x /2 -10 && bird.x + bird.width / 2 < column.x + column.x /2 +10){
                score ++;
            }
            }
            
            if(column.intersects(bird)){                //Collision
                gameover = true;
                if(bird.x <= column.x){
                bird.x = column.x - bird.width; 
                }
                else {
                    if(column.y != 0){
                        bird.y = column.y - bird.height;
                    } else if(bird.y < column.height){
                        bird.y = column.height;
                    }
                }
            }
        }
        if(bird.y > HEIGHT - 150 || bird.y < 0){
            gameover = true;
        }
        if(bird.y + ymotion >= HEIGHT -150){
        bird.y = HEIGHT -150 -bird.height;              //wenn man stirbt, dann bleibt man auf dem boden!
        }
        }
        renderer.repaint();
    }
    
    void repaint(Graphics g) {
       g.setColor(Color.cyan);              //Background
       g.fillRect(0,0,WIDTH,HEIGHT);
       
       g.setColor(Color.green);
       g.fillRect(0, HEIGHT-150, WIDTH, 150);
       
       g.setColor(Color.red);            //bird
       g.fillRect(bird.x, bird.y, bird.width, bird.height);
       
       columns.stream().forEach((column) -> {               //foreach schleife
           paintColumn(g, column);
        });
       
       g.setColor(Color.white);
       g.setFont(new Font("Arial", 1,100));
       if(!started){
           g.drawString("Click to Start!", 75 , HEIGHT / 2 -50);
       }
       if(gameover){
           g.drawString("Game Over!", 100, HEIGHT / 2 -50);
           g.setFont(new Font("Arial", 1, 50));
           g.setColor(Color.white);
           g.drawString("Play Again?", 250,500 );
           g.setFont(new Font("Arial", 1, 25));
           g.drawString("(press Space)", 300, 550);
       }
       
       if(started ){
           g.setFont(new Font("Arial", 1, 50));
           g.drawString("Score: "+ String.valueOf(score), 0, 50);
       }
    }   
    public static void main(String[] args){
        flappybird = new flappyBird();
    } 
    @Override
    public void keyReleased(KeyEvent e) {
       if(e.getKeyCode()== KeyEvent.VK_SPACE){
           jump();
       }
    }

    @Override
    public void keyTyped(KeyEvent e) {
       
    }

    @Override
    public void keyPressed(KeyEvent e) {
       
    }

}

