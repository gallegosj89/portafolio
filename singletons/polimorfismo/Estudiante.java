package polimorfismo;

import java.time.LocalDate;

public class Estudiante extends Persona {
    String carrera;
    int matricula;
    String ciclo;

    public Estudiante(String nombre, int ine, String carrera, int matricula, String ciclo) {
      super(nombre, ine);
      this.nombre=nombre;
      this.ine=ine;
      this.carrera=carrera;
      this.matricula=matricula;
      this.ciclo=ciclo;
    }

    public boolean verificar_cupo(Materia materia) {
      if (materia.getCupo()>= 1) return true;
      return false;
    }

    //método heredado que exhibe conducta propia de la clase hija
    //sobreescritura de método padre
    @Override
    public String inscribirse(String actividad) {
      return "El alumno "+nombre+" INE "+ine+" perteneciente a la carrera "+carrera+" ha completado su inscripción";
    }

    //sobrecarga de método padre
    public String inscribirse(String actividad, LocalDate fecha) {
      return "Inscripción realizada para la actividad "+actividad+" a tener lugar el "+fecha;
    }

    public String inscribirse(Materia materia) {
      if(verificar_cupo(materia)){
          materia.tomarCupo();
          return "Se completó la inscripción en "+materia.titulo;
        }else{
          return "No hay cupo disponible";
        }
    }
}
