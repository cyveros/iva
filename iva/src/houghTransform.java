import java.awt.Point;
import java.util.HashMap;
import java.util.Map;


public class houghTransform {
	private Map<Point, double[]> accumulator;
	private final int SINGLETON_LENGTH = 181, INCREMENT_STEP = 5;
	
	public houghTransform(){
		// 36 division 2 deg per decade
		accumulator = new HashMap<Point, double[]>();
	}
	
	public void add(Point p, double[] singleton){
		accumulator.put(p, singleton);
		
	}
	
	public double[] computeSingleton(Point p){
		double[] d = new double[SINGLETON_LENGTH];
		
		// from 0 to PI (180 deg), increment by 5 deg each time (5 deg is also the threshold value)
		for (int i = 0; i < SINGLETON_LENGTH; i += INCREMENT_STEP){
			d[i] = p.getX() * Math.cos(Math.toRadians(i)) + p.getY() * Math.sin(Math.toRadians(i));
		}
		
		return d;
	}
	
	public void accumulateData(boolean[][] data){
		int width = data.length, height = data[0].length;
		
		for (int i = 0; i < width; i++){
			for (int j = 0; j < height; j++){
				if (data[i][j]){
					Point p = new Point(i, j);
					
					add(p, computeSingleton(p));
				}
				
			}
		}
	}
	
	public int vote(){
		double[][] fusion = new double[accumulator.size()][(SINGLETON_LENGTH - 1)/INCREMENT_STEP];
		int index = 0;
		int retval = -1;
		
		for(double[] d: accumulator.values()){
			for(int i = 0; i < fusion[0].length; i++){
				fusion[index][i] = d[i];
			}
			
			index++;
		}
		
		// compare and find the mostly likely hough trasnform angle in degree for the section
		
		return retval;
	}
	
	public static void main(String[] args){
		

		
	}
}
