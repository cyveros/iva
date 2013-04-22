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
		
		// intersect points using line segment intersect algorithm
		// in a square subsection, we will have 2 intersect points
		int x1 = x, x2 = x + width;
		int y1 = y, y2 = y + height;
		
		bc[2] = 0;
		bc[3] = 0;
		// 2nd intersect point
		bc[4] = 0;
		bc[5] = 0;
		// find intersect
		//
		//if (bc[0] * x1 + bc[1] <= x + width && bc[0] * x1 + bc[1] > x)
		
		
		// need to work out
		
		
		return bc;
	}
}
