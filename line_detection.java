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
		
		//find all the points on the gridg
		double hLimit = 0.05*height;
		double yTemp = 0;
		ArrayList<point> temp = new ArrayList<point>();
		//store the (x, y) in a list
		for (int i = 1; i < height - 3; i++){
			for (int j = 0; j < width - 3; j++){
				if(gridNoise[i][j]){
					hPoints.add(point(i,j));
				}
			}
		}
		
		//split the points into sections and computer linear regression for each section
		for (int k = 0; k < hPoints.size(); k++){
				if(abs(hPoints.get(k).get_y() - yTemp) < hLimit){
					temp.add(hPoints.get(k));
					yTemp = hPoints.get(k).get_y();
				}
				else{
					hLines.add(computeLine(temp));
				}
			}
		}
		
	}
	
	
	public ArrayList<line> getVerticalLine(){
		
		//find all the points on the gridg
		double wLimit = 0.05*width;
		double xTemp = 0;
		ArrayList<point> temp = new ArrayList<point>();
		//store the (x, y) in a list
		for (int i = 0; i < width - 3; i++){
			for (int j = 1; j < height - 3; j++){
				if(gridNoise[i][j]){
					vPoints.add(point(i,j));
				}
			}
		}
		
		//split the points into sections and computer linear regression for each section
		for (int k = 0; k < vPoints.size(); k++){
				if(abs(vPoints.get(k).get_x() - xTemp) < wLimit){
					temp.add(vPoints.get(k));
					xTemp = vPoints.get(k).get_x();
				}
				else{
					vLines.add(computeLine(temp));
				}
			}
		}
		
	}
	
		public ArrayList<line> getDiagonalLine(){
			//find all the points on the gridg
			double dLimit = 0.05*sqrt(width*width + height*height);
			double xTemp = 0;
			double yTemp = 0;
			double xd = 0;
			double yd = 0;
			ArrayList<ArrayList<Point>> temp2 = new ArrayList<ArrayList<point>>();
			ArrayList<point> temp1 = new ArrayList<point>();
			//split the (x, y) to portions
			for (int i = 0; i < width - 3; i++){
				for (int j = 1; j < height - 3; j++){
					if(gridNoise[i][j]){
						xd = i - xTemp;
						yd = j - yTemp;
						if (temp2.isEmpty()){
							if (temp2.isEmpty()){
								
							}
							temp1.add(point(i,j));
							
						}
					}
				}
			}
			
			//split the points into sections and computer linear regression for each section
			/*
			for (int k = 0; k < dPoints.size(); k++){
					double xd = dPoints.get(k).get_x() - xTemp;
					double yd = dPoints.get(k).get_y() - yTemp;
					if(sqrt(xd*xd + yd*yd) < dLimit){
						temp.add(dPoint.get(k));
						xTemp = dPoints.get(k).get_x();
						yTemp = dPoints.get(k).get_y();
						
					}
					else{
						vLines.add(computeLine(temp));
					}
				}
			}*/
		}
	
	
	
	public line computeLine(ArraList<point> pts){
		// y = a + b*x
		int xSum, ySum, xySum, x2Sum;
		double a,b;
		int N = pts.size();
		
		for(int i = 0; i < N; i++){
			xSum = xSum + pts.get(i).get_x();
			ySum = ySum + pts.get(i).get_y();
			xySum = xySum + (pts.get(i).get_x())*(pts.get(i).get_y());
			x2Sum = x2Sum + (pts.get(i).get_x())*(pts.get(i).get_x());
		}
		
		b = (N*xySum - xSum*ySum)/(N*x2Sum - xSum*xSum);
		a = (ySum - b*xSum)/N;
		
		return line(b, a);
	}
	
}
