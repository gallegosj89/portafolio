package polimorfismo;

public class Materia {
    String titulo;
    String carrera;
    int cupo;

    public Materia(String titulo, String carrera) {
        this.titulo=titulo;
        this.carrera=carrera;
        this.cupo=40;
    }

    public int getCupo() {
        return cupo;
    }

    public int tomarCupo() {
        if(cupo==0) return cupo;
        return this.cupo=cupo-1;
    }

    public String getTitulo() {
        return titulo;
    }
}
