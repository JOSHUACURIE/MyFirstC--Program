import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Button{


    public static void main(String[] args) {
        //creating the window
        JFrame frame= new JFrame("Event Driven Programming");
        frame.setSize(300,400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //creation of the components

        JButton button=new JButton("Click Me!");
        JLabel label= new JLabel("Waiting for the event...");


        //Register an event listener
        button.addActionListener(new ActionListener() {
            
            @Override
            public void actionPerformed(ActionEvent e) {
              label.setText("Button was clicked");
                
            }
        });

        //adding components to the panel
        JPanel panel=new JPanel();
        panel.add(button);
        panel.add(label);

        frame.add(panel);
        frame.setVisible(true);
    }
}