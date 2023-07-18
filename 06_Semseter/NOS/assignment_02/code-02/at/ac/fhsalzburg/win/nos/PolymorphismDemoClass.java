package at.ac.fhsalzburg.win.nos;

import java.util.ArrayList;

public class PolymorphismDemoClass {

	public static void main(String[] args) {
		ArrayList<Superclass> array = new ArrayList<Superclass>();
		array.add(new Superclass());
		array.add(new Superclass());
		array.add(new Subclass());
		array.add(new Superclass());
		array.add(new Subclass());
		
		for(int i = 0; i < array.size(); i++) {
			array.get(i).print();
		}
	}

}
