package polimorfismo;

public class Main {
  public static void main(String[] args) {
      // Crear una instancia de Persona
      Persona persona = new Persona("Carlos", 123456);
      System.out.println(persona.inscribirse("Taller de Programación"));

      // Crear una instancia de Materia
      Materia materia = new Materia("Programación Orientada a Objetos", "Ingeniería en Sistemas");
      System.out.println("Cupo inicial de la materia: " + materia.getCupo());

      // Crear una instancia de Estudiante
      Estudiante estudiante = new Estudiante("Ana", 654321, "Ingeniería en Sistemas", 2023001, "2023-2");
      System.out.println(estudiante.inscribirse(materia));

      // Verificar el cupo después de la inscripción
      System.out.println("Cupo restante de la materia: " + materia.getCupo());
  }
}