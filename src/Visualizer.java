import java.awt.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.ZoneOffset;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.WindowConstants;

import org.jfree.chart.*;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.labels.CategoryItemLabelGenerator;
import org.jfree.chart.labels.IntervalCategoryItemLabelGenerator;
import org.jfree.chart.labels.ItemLabelAnchor;
import org.jfree.chart.labels.ItemLabelPosition;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.renderer.category.CategoryItemRenderer;
import org.jfree.chart.renderer.category.GanttRenderer;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.IntervalCategoryDataset;
import org.jfree.data.gantt.Task;
import org.jfree.data.gantt.TaskSeries;
import org.jfree.data.gantt.TaskSeriesCollection;
import org.jfree.data.time.SimpleTimePeriod;
import org.jfree.ui.RefineryUtilities;
import org.jfree.ui.TextAnchor;

public class Visualizer extends JFrame {
    public static final TaskSeriesCollection model = new TaskSeriesCollection();
    public static ArrayList<String> lines;
    public static int makeSpan;
    public static int num_jobs;
    public static int num_machines;


    public Visualizer() {
        super("Gantt Chart");

        //Create the dataset
        createDatasetFromFile();

        // Create chart
        JFreeChart chart = ChartFactory.createGanttChart(
                "Gantt Chart", // Chart title
                "Machines", // X-Axis Label
                "Time", // Y-Axis Label
                model,
                true,
                true,
                false
        );

        final CategoryPlot plot = (CategoryPlot) chart.getPlot();
        DateAxis range = (DateAxis) plot.getRangeAxis();
        range.setDateFormatOverride(new SimpleDateFormat("SSSS"));
        range.setMaximumDate(new Date((makeSpan)));

        // add the chart to a panel...
        final ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(800, 570));
        setContentPane(chartPanel);

        //GanttRenderer personnalis..
        MyRenderer renderer = new MyRenderer(model);
        plot.setRenderer(renderer);




        renderer.setBaseItemLabelsVisible(true);
        renderer.setBasePositiveItemLabelPosition(new ItemLabelPosition(ItemLabelAnchor.INSIDE6, TextAnchor.CENTER_LEFT));

        //Update legend to reflect correct color
        LegendItemCollection chartLegend = new LegendItemCollection();
        Shape shape = new Rectangle(10, 10);
        for (int i = 0; i < num_jobs; i++) {
            chartLegend.add(new LegendItem("Job " + (i + 1), null, null, null, shape, renderer.colorList[i]));
        }
        plot.setFixedLegendItems(chartLegend);

        plot.setBackgroundPaint(Color.WHITE);
    }

    private static class MyRenderer extends GanttRenderer {
        private static final int PASS = 2; //Assumes two passes. Unsure what the fuck it does
        private final Color[] colorList = getUniqueColors(num_jobs);
        private final List<Color> clut = new ArrayList<>();
        private final TaskSeriesCollection model;
        private int row;
        private int col;
        private int index;

        public MyRenderer(TaskSeriesCollection model) {
            this.model = model;
        }

        @Override
        public Paint getItemPaint(int row, int col) {
            if (clut.isEmpty() || this.row != row || this.col != col) {
                fillColorList(row, col);
                this.row = row;
                this.col = col;
                index = 0;
            }
            int colorIndex = index++ / PASS;
            return clut.get(colorIndex);
        }

        //Se på tidligere. Modifiser og lag en ny liste basert på beskrivelsen til subtasken. Fyll inn den listen med de fargene så burde det funke

        private void fillColorList(int row, int col) {
            clut.clear();


            TaskSeries series = (TaskSeries) model.getRowKeys().get(row);
            List<Task> tasks = series.getTasks(); // unchecked

            int taskCount = tasks.get(col).getSubtaskCount();
            taskCount = Math.max(1, taskCount);

            //System.out.println("----> " + taskCount);
            String description;

            for (int i = 0; i < taskCount; i++) {
                description = tasks.get(col).getSubtask(i).getDescription();
                //System.out.println("Description for substask is: " + description);
                //Might need to change
                clut.add(colorList[Integer.parseInt(description)]);
            }
        }

        //Method for generating a list of unique colors. From: https://stackoverflow.com/questions/3403826/how-to-dynamically-compute-a-list-of-colors
        Color[] getUniqueColors(int amount) {
            Color[] cols = new Color[amount];
            for (int i = 0; i < amount; i++) {
                cols[i] = Color.getHSBColor((float) i / amount, 1, 1);
            }
            return cols;
        }
    }


    private void createDatasetFromFile() {

        try{
            solutionReader();
        }
        catch(IOException ex){

        }

        TaskSeries series = new TaskSeries("Schedule");
        for(int i = 0; i < num_machines; i++){
            Task job = new Task("Machine " + i, new SimpleTimePeriod(0, makeSpan + 5));
            series.add(job);
        }

        for(int i = 0; i < lines.size(); i++){
            // jobID temp[0]
            // machineID temp[1]
            // start temp[2]
            // end temp[3]
            String[] vals = lines.get(i).split(" ");
            int jobID = Integer.parseInt(vals[0]);
            int machineID = Integer.parseInt(vals[1]);
            int startTime = Integer.parseInt(vals[2]);
            int endTime = Integer.parseInt(vals[3]);
            series.get(machineID).addSubtask(new Task("" + jobID, new SimpleTimePeriod(startTime, endTime)));

        }
        model.add(series);

    }


    public static void solutionReader() throws IOException {
        FileReader filereader = new FileReader("src/solution.txt");
        BufferedReader bufferedReader = new BufferedReader(filereader);

        String line = null;
        //list for storing data from the file
        lines = new ArrayList<>();

        //add lines to the list
        boolean firstLine = true;
        while ((line = bufferedReader.readLine()) != null){
            if(firstLine){
                String[] temp = line.split(" ");
                makeSpan = Integer.parseInt(temp[0]);
                num_jobs = Integer.parseInt(temp[1]);
                num_machines = Integer.parseInt(temp[2]);
                firstLine = false;
            }
            else{
                lines.add(line);
            }

        }

        bufferedReader.close();
    }


    public static void main(String[] args) {
        Visualizer vis = new Visualizer();

        vis.pack();
        RefineryUtilities.centerFrameOnScreen(vis);
        vis.setVisible(true);


    }


}