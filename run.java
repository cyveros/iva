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
		iva x = new iva(imgPath);
		// perform basic configuration
		x.preComputation();
		
		// edge detection
		x.gradientSmoother();
		x.output();
		
		// noise reduction (feature extract)
		x.noiseReduction();
		
		x.output("o_test2.png");
	}
}
