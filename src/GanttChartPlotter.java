import javax.swing.*;


import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.category.IntervalCategoryDataset;
import org.jfree.data.gantt.Task;
import org.jfree.data.gantt.TaskSeries;
import org.jfree.data.gantt.TaskSeriesCollection;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.RoundRectangle2D;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.List;

/**
 * Created by Andreas on 09.04.2019.
 */
public class GanttChartPlotter extends JPanel {

    public static final TaskSeriesCollection model = new TaskSeriesCollection();
    public ArrayList<String> lines;


    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        String delimiter = " ";

        Dimension size = getSize();
        Color[] depotColors = {Color.RED, Color.GREEN, Color.YELLOW, Color.BLUE,
                Color.PINK, Color.CYAN, Color.MAGENTA, Color.GRAY,
                Color.orange};
        for(int i = 0; i < lines.size(); i++){
            String[] temp = lines.get(i).split(delimiter);
            //draw using fill rect here
            // jobID temp[0]
            // machineID temp[1]
            // start temp[2]
            // end temp[3]

        }



    }


    public GanttChartPlotter() {


    }


    public void solutionReader() throws IOException{
        FileReader filereader = new FileReader("src/solution.txt");
        BufferedReader bufferedReader = new BufferedReader(filereader);

        String line = null;
        //list for storing data from the file
        lines = new ArrayList<>();

        //add lines to the list
        while ((line = bufferedReader.readLine()) != null){
            lines.add(line);
        }

        bufferedReader.close();
    }


    public static void main(String arg[]) {

        GanttChartPlotter g = new GanttChartPlotter();
        try{
            g.solutionReader();
        }
        catch(IOException ex){

        }

        //Draw the problem
        JFrame frame = new JFrame("Points");

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(g);
        int frameWidth = 1000;
        int frameHeight = 1000;
        //Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        //frame.setBounds((int) screenSize.getWidth() - frameWidth, 0, frameWidth, frameHeight);
        frame.setSize(new Dimension(frameWidth, frameHeight));
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);


    }
}



