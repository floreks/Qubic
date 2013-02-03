package org.marmac.first;

import org.kornicameister.tutorial.qubic.Event;
import org.kornicameister.tutorial.qubic2.Calendar;
import org.kornicameister.tutorial.qubic2.User;

import java.util.Collection;
import java.util.Iterator;
import java.util.Set;

/**
 * Created with IntelliJ IDEA.
 * User: Marcin
 * Date: 03.02.13
 * Time: 14:58
 * To change this template use File | Settings | File Templates.
 */
public class HelloWorld
{
    public static void main(String... args)
    {
        System.out.println("Hello World!");

        User me = new User("Marcin","Maciaszczyk");
        Calendar cal = new Calendar("Kalendarz 2013",me);
    }
}
