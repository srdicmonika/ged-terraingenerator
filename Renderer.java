package flappyBird;

import java.awt.Graphics;
import javax.swing.JPanel;

public class Renderer extends JPanel{             //erstellt eigenen Jpanel (Aussehen)
    
    @Override
    protected void paintComponent(Graphics g){
        super.paintComponent(g);
        flappyBird.flappybird.repaint(g);
        
    }
}
