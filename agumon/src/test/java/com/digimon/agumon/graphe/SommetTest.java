package com.digimon.agumon.graphe;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SommetTest {
    Sommet s = new Sommet("Metz",null,40);
    Sommet v = new Sommet("Paris",s,300);

    @Test
    void testSimpleSommet(){
        assertEquals(40, s.getDistance());
        assertNotEquals(49,s.getDistance());
        assertEquals("Metz",s.getNom());
        assertNull(s.getPredecesseur());
    }

    @Test
    void testSommetAvecPred(){
//        System.out.println(v);
        assertEquals(s,v.getPredecesseur());
        assertEquals(40,v.getPredecesseur().getDistance());
        assertEquals(300,v.getDistance());
    }

}