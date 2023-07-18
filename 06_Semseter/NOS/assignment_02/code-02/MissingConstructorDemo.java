import at.ac.fhsalzburg.win.nos.AnotherClassesDemoClass;
import at.ac.fhsalzburg.win.nos.ClassesDemoClass;

public class DemoMainClass {
	public static void main(String[] args) {
		/* creates new instance */
		ClassesDemoClass cdc = new ClassesDemoClass();
		/* does not work as no default constructor is created 
		 * if there already is an explicit constructor
		 */
		AnotherClassesDemoClass cdc2 = new AnotherClassesDemoClass();	
		
		DemoMainClass dmc = new DemoMainClass();
		
		int a = 5;
		
		dmc.changeValues(a);
		System.out.println(a);
		dmc.changeValues(cdc);
		System.out.println(cdc);
	}
	
	// Does not change the value outside of the method.
	public void changeValues(int x) {
		x = 7;
	}
	
	// Changes the value since a copy of the object reference is passed to the method.
	public void changeValues(ClassesDemoClass cdc) {
		cdc.a = 13;
	}

}
