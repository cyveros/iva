import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.math.*;
import java.util.ArrayList;

public class line_detection { 

	private ArrayList<line> hLines = new ArrayList<line>();
	private ArrayList<line> vLines = new ArrayList<line>();
	private ArrayList<line> dLines = new ArrayList<line>();
	private ArrayList<point> hPoints = new ArrayList<point>();
	private ArrayList<point> vPoints = new ArrayList<point>();
	private ArrayList<point> dPoints = new ArrayList<point>();
	private boolean[][] gridNoise;
	private int height, width;
	
	public line_detection(boolean[][] grid, int h, int w){
		this.gridNoise = grid;
		this.height = h;
		this.width = w;
	}
	
	public ArrayList<line> getHorizontalLine(){
		
		//find all the points on the grid
		public int k = 0;
		for (int i = 1; i < height - 3; i++){
			for (int j = 0; j < width - 3; j++){
				if(gridNoise[i][j]){
					hPoints.add(k, point(i,j));
					k++;
				}
			}
		}
		
		//split the points into sections
		
	}
	
	
}
