import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.math.*;

public class line {
	
	private double m = 0; //slope
	private double c = 0; //y intercept

	public point (double m, double c){
		this.m = m;
		this.c = c;
	}

	public double get_m(){
		return m;
	}
		
	public double get_c(){
		return c;
}
} 	


