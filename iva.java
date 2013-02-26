import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.math.*;

/**
 * This class demonstrates how to load an Image from an external file
 */
public class iva {
          
    private BufferedImage img = null;
    private int width, height;
    private double numberOfPixels;
    
    private double mean = 0, std = 0;
    // some common color code
    private final int white = 0xFFFFFF, black = 0, grey = 0x808080;
    // factor
    private final double upper = 1.25, lower = 0.75;
    
    public iva(String imgPath){
		try {
			img = ImageIO.read(new File(imgPath));
			getProperties();
			
		} catch (IOException e){
			e.printStackTrace();
		}
	}
    
    public iva(BufferedImage img){
		this.img = img;
		getProperties();
	}
	
	public iva(iva x){
		this.img = x.getBufferedImage();
		
		this.height = x.getHeight();
		this.width = x.getWidth();
		this.numberOfPixels = height * width;
		
		this.mean = x.getMean();
		this.std = x.getStandardDeviation();
	}
	
	public void computeMean(){
		for(int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				mean += (double)getAlphalessRGB(i, j) / numberOfPixels;
	}
	
	// computeMean() must be called before computing standard deviation
	public void computeStandardDeviation(){
		for(int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				std += Math.pow((double)getAlphalessRGB(i, j) - mean, 2) / numberOfPixels;
				
		std = Math.sqrt(std);
	}
	
	public int getAlphalessRGB(int x, int y){
		return img.getRGB(x, y) & 0xFFFFFF;
	}
	
	public BufferedImage getBufferedImage(){
		return this.img;
	}
	
	public int getHeight(){
		return height;
	}
	
	public double getMean(){
		return mean;
		
	}
	
	public double getStandardDeviation(){
		return std;
	}
	
	public void getProperties(){
		width = img.getWidth();
		height = img.getHeight();
		
		numberOfPixels = width * height;
	}
	
	public int getWidth(){
		return width;
	}
	
	public void gradientSmoother(){
		// assume mean and std is computed
		int color;
		
		for(int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				color = getAlphalessRGB(i, j);
				
				if ((double)color > mean + (double)upper * std){
					setColor(i, j, white);
					//System.out.println("color:\t" + color + ", compared:\t" + (mean + (double)white * std) + ", white");
				}else if ((double)color < mean - (double)lower * std){
					setColor(i, j, black);
					//System.out.println("color:\t" + color + ", compared:\t" + (mean - (double)black * std) + ", black");
				}else{
					setColor(i, j, grey);
					//System.out.println("color:\t" + color + ", compared:\t" + (mean + (double)black * std) + "," + (mean - (double)black * std) + "  grey");
				}
			}
		}
	}
	
	public void noiseReduction(){
		
		boolean[][] gridVerticalNoise = new boolean[width][height];
		
		for (int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				if (noiseVerticalReduction(i, j)){
					// set grid values
					gridVerticalNoise[i][j] = true;
					
					
				}
				else{
					gridVerticalNoise[i][j] = false;
				}
			}
		}
		
		// reduce color noise by reset to color to white or black
		// to be implemented
	}
	
	// return a boolean flag whether there exists noise within 3 x 3 section of pixels
	public boolean noiseVerticalReduction(int i, int j){

		// Out of bounds, do not calculate
		if (width <= i + 2 || height <= j + 2)
			return false;
		
		double verticalSumR = 0, verticalSumL = 0, verticalAvrgR, verticalAvrgL,
			   remainderSumR = 0, remainderSumL = 0, remainderAvrgR, remainderAvrgL;
			   
        // Analysis 3X3 space
        // vertical Left *, Right #, middle - 
        // * - #
        // * - #
        // * - #
        
		verticalSumR += img.getRGB(i + 2, j) + img.getRGB(i + 2, j + 1) + img.getRGB(i + 2, j + 2);
		verticalAvrgR = verticalSumR / 3;

		verticalSumL += img.getRGB(i, j) + img.getRGB(i, j + 1) + img.getRGB(i, j + 2);
		verticalAvrgL = verticalSumL / 3;

		remainderSumR = verticalSumL + img.getRGB(i + 1, j) + img.getRGB(i + 1, j + 1) + img.getRGB(i + 1, j + 2);
		
		
		// ??? remainderAvrgR is never used
		remainderAvrgR = remainderSumR / 6;

		remainderSumL = remainderSumR - verticalSumL + verticalSumR ;

		remainderAvrgL = remainderSumL / 6;


        if (verticalAvrgL > remainderAvrgL)
			return true;
			
		return false;
		
	}
	
	public void output(){
		outputImage("o_test.png", "PNG");
	}
	
	public void output(String fileName){
		outputImage(fileName, "PNG");
	}
	
	public void outputImage(String fileName, String type){
		try {
			File f = new File(fileName);
			ImageIO.write(img, type, f);
		} catch (IOException e){
			e.printStackTrace();
		} 
	}
	
	
	
	public void preComputation(){
		// pre computation steps
		computeMean();
		computeStandardDeviation();
	}
	
	public void setColor(int x, int y, int color){
		img.setRGB(x, y, 0xFF000000 | color);
	}
	
	public void setImage(BufferedImage img){
		this.img = img;
		getProperties();
	}

}


