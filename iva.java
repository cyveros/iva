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
          
    private BufferedImage in, out;
    private int width, height;
    private double numberOfPixels;
    
    private double mean = 0, std = 0;
    private final int white = 0xFFFFFF, black = 0, grey = 0x808080;
    private final double upper = 1.25, lower = 0.75;
    
    public iva(String imgPath){
		try {
			in = ImageIO.read(new File(imgPath));
			getProperties();
			
		} catch (IOException e){
			e.printStackTrace();
		}
	}
    
    public iva(BufferedImage img){
		this.in = img;
		getProperties();
	}
	
	public void createOuputImage(){
		out = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
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
		return in.getRGB(x, y) & 0xFFFFFF;
	}
	
	public int getHeight(){
		return height;
	}
	
	
	
	public void getProperties(){
		width = in.getWidth();
		height = in.getHeight();
		
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
		
	}
	
	public void outputImage(String fileName, String type){
		try {
			File f = new File(fileName);
			ImageIO.write(out, type, f);
		} catch (IOException e){
			e.printStackTrace();
		} 
	}
	
	public void output(){
		outputImage("o_test.png", "PNG");
	}
	
	public void preComputation(){
		// pre computation steps
		computeMean();
		computeStandardDeviation();
		// create output image
		createOuputImage();
	}
	
	public void setColor(int x, int y, int color){
		out.setRGB(x, y, 0xFF000000 | color);
	}
	
	public void setImage(BufferedImage img){
		this.in = img;
		getProperties();
	}

}


