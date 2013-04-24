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
		//int x1 = x, x2 = x + width;
		//int y1 = y, y2 = y + height;
		int cursor = 0;
		int intersectCount = 0;
		
		bc[2] = 0;
		bc[3] = 0;
		// 2nd intersect point
		bc[4] = 0;
		bc[5] = 0;
		// find intersect
		// left
		while (intersectCount < 2){
			// left
			if (cursor == 0){
				if (bc[0] * x + bc[1] <= y + height && bc[0] * x + bc[1] >= y){
					if (intersectCount == 0){
						bc[2] = x;
						bc[3] = bc[0] * x + bc[1];
					}else{
						bc[4] = x;
						bc[5] = bc[0] * x + bc[1];
					}
					
					intersectCount++;
				}
				
				cursor++;
				
			}else if(cursor == 1){ // bottom
				if ((y - bc[1])/ bc[0] <= x + width && (y - bc[1])/ bc[0] >= x){
					if (intersectCount == 0){
						bc[2] = (y - bc[1])/ bc[0];
						bc[3] = y;
					}else{
						bc[4] = (y - bc[1])/ bc[0];
						bc[5] = y;
					}
					
					intersectCount++;
				}
				
				cursor++;
			}else if(cursor == 2){ // right
				if (bc[0] * (x + width) + bc[1] <= y + height && bc[0] * (x + width) + bc[1] >= y){
					if (intersectCount == 0){
						bc[2] = (x + width);
						bc[3] = bc[0] * (x + width) + bc[1];
					}else{
						bc[4] = (x + width);
						bc[5] = bc[0] * (x + width) + bc[1];
					}
					
					intersectCount++;
				}
				
				cursor++;
			}else{ // top
				if ((y + height - bc[1])/ bc[0] <= x + width && (y + height - bc[1])/ bc[0] >= x){
					if (intersectCount == 0){
						bc[2] = (y + height - bc[1])/ bc[0];
						bc[3] = y + height;
					}else{
						bc[4] = (y + height - bc[1])/ bc[0];
						bc[5] = y + height;
					}
					
					intersectCount++;
				}
				
				cursor++;
			}
			
		}
		
		
		return bc;
	}
}
