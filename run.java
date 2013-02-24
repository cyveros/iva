import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.math.*;

public class run {
	
	private static String imgPath;
	private static BufferedImage img;
	private static int h,w;
	private static int totalDots;
	private static double medium = 0;
	private static double std = 0; // standard deviation

	
	public static int getAlphalessRGB(int x, int y){
		return img.getRGB(0, 0) & 0xFFFFFF;
		
	}
	
	public static void main(String[] args){
		imgPath = args[0];
	
		try {
			img = ImageIO.read(new File(imgPath));
			
		} catch (IOException e){
			
		}
		
		h = img.getHeight();
		w = img.getWidth();
		totalDots = h*w;
		
		System.out.println(getAlphalessRGB(0, 0) + "\t" + Integer.toBinaryString(getAlphalessRGB(0, 0)));
		
		for(int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				medium += (double)getAlphalessRGB(i, j) / totalDots;
		
		for(int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				std += Math.pow((double)getAlphalessRGB(i, j) - medium, 2) / totalDots;
		
		std = Math.sqrt(std);
		
		// next step to filter the pixel into black, white, grey
		for(int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				
			}
		}
		System.out.println("standard deviation\t" + std);
	}
}