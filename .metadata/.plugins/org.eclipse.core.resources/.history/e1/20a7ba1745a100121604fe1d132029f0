
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.util.ArrayList;

import javax.swing.*;

public class ivaApp extends Component{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * 
	 */
	private ArrayList<BufferedImage> imgs;
	int width, height;
	int countHorizontal = 0, countVertical = 0;

    public void paint(Graphics g) {
    	
    	if (imgs.size() > 0){
    		for (BufferedImage img: imgs){
    			if (countHorizontal >= 3){
    				countHorizontal = 0;
    				++countVertical;
    			}
    			
    			g.drawImage(img, countHorizontal * width, countVertical * height, null);
    			System.out.println("x: " + countHorizontal + ", y: " + countVertical);
    			++countHorizontal;
    				
    		}
    	}
        
    }

    public ivaApp(ArrayList<BufferedImage> imgs) {
       this.imgs = imgs;
       
       width = imgs.get(0).getWidth();
       height = imgs.get(0).getHeight();
       
    }

    public Dimension getPreferredSize() {
        if (imgs.size() == 0) {
             return new Dimension(100,100);
        } else {
           return new Dimension(width * 3, height * 6);
       }
    }

    public static void main(String[] args) {
    	// prep before render layouts
    	String imgPath = args[0];
		String outputPath = "";
		ArrayList<BufferedImage> bis = new ArrayList<BufferedImage>();
		
		if (args.length > 1)
			outputPath = args[1];

		// port from cpp source code
		// create iva object
		iva image = new iva(imgPath);
		
		if (outputPath.length() > 1)
			image.setOutputPath(outputPath);
		
		// perform basic configuration
		image.preComputation();
		
		// edge detection
		image.gradientSmoother();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 1 - Image Grating Complete");
		
		image.noiseReduction();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 2 - Feature Extract Complete");

		image.lineComplete();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 3 - Line Completion complete");
		
		image.noiseReduction(true);
		bis.add(image.getBufferedImage());
		System.out.println("Stage 4 - Post-processing complete");
		
		image.lineThinningComplete();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 5 - Line Thinning complete");
		
		image.colorImageComplete();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 6 - Image Coloring complete");
		
		image.lineDrawComplete();
		bis.add(image.getBufferedImage());
		System.out.println("Stage 7 - Line draw complete");
		
		// shape detection
		
		
		image.imageJet();
		bis.add(image.getBufferedImage());
		System.out.println("Stage X - Image jet complete");

        JFrame f = new JFrame("Image Vision Analysis");
            
        f.addWindowListener(new WindowAdapter(){
                public void windowClosing(WindowEvent e) {
                    System.exit(0);
                }
            });

        f.add(new ivaApp(bis));
        f.pack();
        f.setVisible(true);
    }
}



