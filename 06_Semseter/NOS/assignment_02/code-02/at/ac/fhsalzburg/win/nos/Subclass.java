package at.ac.fhsalzburg.win.nos;

public class Subclass extends Superclass {
	
	public Subclass() {
		super();
		valueB *= 2;
	}
	
	@Override
	public void print() {
		super.print();
		System.out.println("Subclass: " + valueB);
	}

}
