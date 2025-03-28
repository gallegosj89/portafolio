package polimorfismo;

public class Persona {
    String nombre;
    int ine;

    public Persona(String nombre, int ine){
      this.nombre = nombre;
      this.ine = ine;
    }

    public String inscribirse(String actividad){
      return "La inscripción de "+nombre+" para "+actividad+" se ha realizado satisfactoriamente.";
    }
}