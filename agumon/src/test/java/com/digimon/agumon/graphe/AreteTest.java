package com.digimon.agumon.graphe;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AreteTest {
    Sommet u = new Sommet("Metz",null,34);
    Sommet v = new Sommet("Paris",u,50);
    Arete a = new Arete(u,v,500);

    @Test
    void testArete(){
        assertEquals(500,a.getDistance());
        assertEquals(u,a.getA());
        assertEquals(v,a.getB());
//        System.out.println(a);
    }

}