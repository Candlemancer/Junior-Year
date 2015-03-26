# Jonathan Petersen
# A01236750
# Blur Detection Assignment
# Starter Code

from PIL import Image
from PIL import ImageFilter
import Detect_Edges_Gradients


# Edge-finding Algorithm
def filterFindEdges(im):
	
	filePrefix = "Blurry_Sample	";
	fileSuffix = " Edges.jpg";
	outputFile = filePrefix + "" + fileSuffix;

	# im1 = im.filter(ImageFilter.FIND_EDGES)
	im1 = Detect_Edges_Gradients.detect_rgb_edges(im);

	im1.save(outputFile)





# Driver Code
filePrefix = "Blurry_Sample";
fileSuffix = ".jpg";
imageFile = filePrefix + "" + fileSuffix;
im1 = Image.open(imageFile)

filterFindEdges(im1)
	
