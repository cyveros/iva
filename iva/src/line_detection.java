import java.awt.*;
import java.util.ArrayList;

public class line_detection { 

	private ArrayList<Point> hLines = new ArrayList<Point>();
	private ArrayList<Point> vLines = new ArrayList<Point>();
	private ArrayList<Point> dLines = new ArrayList<Point>();
	private ArrayList<Point> hPoints = new ArrayList<Point>();
	private ArrayList<Point> vPoints = new ArrayList<Point>();
	private ArrayList<Point> dPoints = new ArrayList<Point>();
	private boolean[][] gridNoise;
	private int height, width;
	
	public line_detection(boolean[][] grid, int h, int w){
		this.gridNoise = grid;
		this.height = h;
		this.width = w;
	}
	
	public ArrayList<Point> getHorizontalLine(){
		
		//find all the points on the grid
		double hLimit = 0.05*height;
		double yTemp = 0;
		ArrayList<Point> temp = new ArrayList<Point>();
		//store the (x, y) in a list
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				if(gridNoise[i][j]){
					hPoints.add(new Point(i,j));
				}
			}
		}
		
		//split the points into sections and computer linear regression for each section
		for (int k = 0; k < hPoints.size(); k++){
				if(Math.abs(hPoints.get(k).getY() - yTemp) < hLimit){
					temp.add(hPoints.get(k));
					yTemp = hPoints.get(k).getY();
				}
				else{
					hLines.add(computeLine(temp));
				}
			}
		return hLines;
		}
		
	
	
	
	public ArrayList<Point> getVerticalLine(){
		
		//find all the points on the grid
		double wLimit = 0.05*width;
		double xTemp = 0;
		ArrayList<Point> temp = new ArrayList<Point>();
		//store the (x, y) in a list
		for (int i = 0; i < width - 3; i++){
			for (int j = 1; j < height - 3; j++){
				if(gridNoise[i][j]){
					vPoints.add(new Point(i,j));
				}
			}
		}
		
		//split the points into sections and computer linear regression for each section
		for (int k = 0; k < vPoints.size(); k++){
				if(Math.abs(vPoints.get(k).getX() - xTemp) < wLimit){
					temp.add(vPoints.get(k));
					xTemp = vPoints.get(k).getX();
				}
				else{
					vLines.add(computeLine(temp));
				}
			}
		return vLines;
		}
		
	
	
		public ArrayList<Point> getDiagonalLine(){
			//find all the points on the grid
			double dLimit = 0.05*(width*width + height*height);
			double xTemp = 0;
			double yTemp = 0;
			ArrayList<ArrayList<Point>> temp2 = new ArrayList<ArrayList<Point>>();
			ArrayList<Point> temp1 = new ArrayList<Point>();

			//split the (x, y) to portions
			for (int i = 0; i < width; i++){
				for (int j = 0; j < height; j++){
					if(gridNoise[i][j]){
						
						if (temp2.isEmpty()){
							temp2.get(0).add(new Point(i,j));
						}
						
						else{
							//for each set of points
							for(int k = 0; k < temp2.size(); k++){
								temp1 = temp2.get(k);
								
								/*if(temp1.isEmpty()){
									temp1.add(new Point(i,j));
								}
								
								else{
									*/
								
									int l = temp1.size() - 1;
									xTemp = i - temp1.get(l).getX();
									yTemp = j - temp1.get(l).getY();
										
									if((xTemp*xTemp + yTemp*yTemp) < dLimit){
										
										temp1.add(new Point(i,j));
										break;
									}
									
										
								}
								temp2.get(k+1).add(new Point(i,j));
							}
				
						}
					}
				}
			
		//find linear regression of each set of points	
			for (int n = 0; n < temp2.size(); n++){
				dLines.add(computeLine(temp2.get(n)));
			}
		return dLines;
		}
	
	
	
	public Point computeLine(ArrayList<Point> pts){
		// y = a + b*x
		double xSum = 0, ySum = 0, xySum = 0, x2Sum = 0;
		double a,b;
		int N = pts.size();
		Point pt = new Point();
		
		for(int i = 0; i < N; i++){
			xSum = xSum + pts.get(i).getX();
			ySum = ySum + pts.get(i).getY();
			xySum = xySum + (pts.get(i).getX())*(pts.get(i).getY());
			x2Sum = x2Sum + (pts.get(i).getX())*(pts.get(i).getX());
		}
		
		b = (N*xySum - xSum*ySum)/(N*x2Sum - xSum*xSum);
		a = (ySum - b*xSum)/N;
		pt.setLocation(b, a);
		
		return pt;
	}
	
	public static void main(String[] args){
		
		boolean[][] test = new boolean[20][20];
		
		for (int i = 4; i < 20; i += 5){
			
			for (int j = 4; j < 15 ; j++)
				test[i][j] = true;
		}
		
		
		line_detection ld = new line_detection(test, 20, 20);
		
		ArrayList<Point> lp = ld.getHorizontalLine();
		
		int index = 0;
		for(Point p: lp){
			
			System.out.println(index + " " + p.getX() + " " + p.getY());
			index++;
		}
		
	}
	
}
