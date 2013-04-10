import java.awt.Point;


public class lineVector {
	private Point p;
	private int x, y, width, height;
	
	public lineVector(Point polar, int x, int width, int y, int height){
		
		this.p = polar;
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		
	}
	
	public double[] getBoundaryCoordinates(){
		
		double[] bc = new double[6];
		
		// y = mx + b
		bc[0] = -1 * Math.cos(Math.toRadians(p.getY())) / Math.sin(Math.toRadians(p.getY())); // m
		bc[1] = p.getX() / Math.sin(Math.toRadians(p.getY())); // b
		
		// intersect points
		// need to work out
		
		
		return bc;
	}
}
