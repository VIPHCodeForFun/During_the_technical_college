package at.ac.fhsalzburg.win.nos;

public class ClassesDemoClass {
	private int x, y, z;
	public int a;
	
	public void setValues(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public ClassesDemoClass() {
		x = 1;
		y = 1;
	}
	
	public ClassesDemoClass(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public ClassesDemoClass(int factor) {
		this();
		x *= factor;
		y *= factor;
	} 
	
	{
		z = 5;
	}
	
	
}
