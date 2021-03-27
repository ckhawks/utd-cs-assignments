import java.util.Scanner;

public class ivan1 {
    public static void main(String[] args) {

        // take in the user input
        Scanner s = new Scanner(System.in);
        System.out.print("Enter the variable name: ");
        String var_name = s.nextLine();
        if(var_name.contains(" ")){ // if it has multiple words
            var_name = var_name.substring(0, var_name.indexOf(" ")); // split off only the first word of input
        }

        System.out.print("Enter a number: ");
        String num = s.next();

        System.out.println(); // add a line break between input and output

        // format first two lines of output properly depending on if using integer or double
        String output = "";
        if(num.contains(".")){ // check if inputted number has a period
            // number is double
            output = "double " + var_name + " = " + num + ";\nif(" + var_name + " > 0){\n";
        } else {
            // number is int
            output = "int " + var_name + " = " + num + ";\nif(" + var_name + " > 0){\n";
        }

        // add the rest of the output that stays the same
        output = output + "    System.out.println(\"Positive.\");\n}else{\n    System.out.println(\"Negative or Zero. \");\n}";
        System.out.println(output); // print the final output
    }
}
