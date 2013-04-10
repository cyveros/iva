public class run {
	
	public static void main(String[] args){
		String imgPath = args[0];
		String outputPath = "";
		
		if (args.length > 1)
			outputPath = args[1];

		// port from cpp source code
		// create iva object
		iva image = new iva(imgPath);
		
		if (outputPath.length() > 1)
			image.setOutputPath(outputPath);
		
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
		
		image.lineDrawComplete();
		System.out.println("Stage 7 - Line draw complete");
		
		// shape detection
		
		
		image.imageJet();
		System.out.println("Stage X - Image jet complete");
		
	}
}
