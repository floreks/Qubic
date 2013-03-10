package org.kornicameister.tutorial.qubic;

import org.kornicameister.tutorial.qubic2.Calendar;

import javax.persistence.*;
import java.util.Collection;
import java.util.Date;

/**
 * Event model.</br>
 * <p>
 * This class is different from its ancestor. It is not
 * described as {@link MappedSuperclass} but as {@link Entity}.
 * This comes with significant advantages:
 * <ul>
 * <li>
 * the class will have its equivalent in the database
 * existing under the name specified in
 * {@link Table}'s name argument
 * </li>
 * <li>
 * class may contain dozens of additional fields
 * and they all will be reflected in the corresponding
 * table in the database. For instances, here we have:
 * <ul>
 * <li>{@link Event#title}</li>
 * <li>{@link Event#modifiedAt}</li>
 * </ul>
 * </li>
 * </ul>
 * </p>
 *
 * @author kornicameister
 * @version 0.1
 * @see org.kornicameister.tutorial.qubic.Event#hashCode()
 * @since 2013-01-27
 */
@Entity
@Table(name = "event")
public class Event extends IDModel {
    @Column(name = "title", insertable = true, nullable = false, updatable = true)
    private String title;

    @Column(name = "date", insertable = true, nullable = false)
    private Date eventDate;

    /**
     * One of the quite cool things about Hibernate is that it allows us
     * to create some sort of bidirectional association between two models.
     * For instance this field is not directly described as being an
     * association part, but in my opinion this goal is achieved indirectly.
     *
     * @see Calendar#events for more information
     */
    @ManyToMany(mappedBy = "events")
    private Collection<Calendar> calendars;

    public Event() {
        super();
        this.eventDate = new Date();
    }

    public Event(String title) {
        super();
        this.title = title;
        this.eventDate = new Date();
    }

    public Event(String title, Date eventDate) {
        super();
        this.title = title;
        this.eventDate = eventDate;
    }

    public Collection<Calendar> getCalendars() {
        return calendars;
    }

    public void setCalendars(Collection<Calendar> calendars) {
        this.calendars = calendars;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Event)) return false;
        if (!super.equals(o)) return false;

        Event event = (Event) o;

        if (eventDate != null ? !eventDate.equals(event.eventDate) : event.eventDate != null) return false;
        if (title != null ? !title.equals(event.title) : event.title != null) return false;

        return true;
    }

    /**
     * Overriding {@link IDModel#hashCode()} method
     * may not be necessary if auto incremented primary key is used. The situation
     * of the two rows (entities) and what comes with that - models is simple
     * not possible.
     *
     * @return value of comparison
     */
    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (title != null ? title.hashCode() : 0);
        result = 31 * result + (eventDate != null ? eventDate.hashCode() : 0);
        return result;
    }
}
