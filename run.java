import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.math.*;

public class run {
	
	public static void main(String[] args){
		String imgPath = args[0];
		
		// create iva object
		iva image = new iva(imgPath);
		// perform basic configuration
		image.preComputation();
		
		// edge detection
		image.gradientSmoother();
		System.out.println("Stage 1 - Image Grating Complete");
		
		image.noiseReduction();
		System.out.println("Stage 2 - Feature Extract Complete");

		image.lineComplete();
		System.out.println("Stage 3 - Line Completion complete");
		
		image.noiseReduction(true);
		System.out.println("Stage 4 - Post-processing complete");
		
		image.lineThinningComplete();
		System.out.println("Stage 5 - Line Thinning complete");
		
		image.colorImageComplete();
		System.out.println("Stage 6 - Image Coloring complete");
	}
}
