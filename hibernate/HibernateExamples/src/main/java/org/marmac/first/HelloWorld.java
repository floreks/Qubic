package org.marmac.first;

import org.kornicameister.tutorial.qubic2.Calendar;
import org.kornicameister.tutorial.qubic2.User;

public class HelloWorld
{
    public static void main(String... args)
    {
        System.out.println("Hello World!");

        User me = new User("Marcin","Maciaszczyk");
        Calendar cal = new Calendar("Kalendarz 2013",me);
    }
}
