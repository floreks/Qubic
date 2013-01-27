package org.kornicameister.tutorial.qubic;

import javax.persistence.*;
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
 * <li>{@link Event#date}</li>
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
public class Event extends PersistenceObject {
    @Column(name = "title", insertable = true, nullable = false, updatable = true)
    private String title;

    /**
     * When the class' field is declared with {@link Temporal} annotation
     * and this field is initialized in each one of the class' constructors, than
     * one thing is more than sure. Hibernate will take care of updating this field.
     * This feature is quite useful if you would like to have a column
     * in database that will hold information about recent row's access.
     */
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "lastAccess")
    private Date date;


    public Event() {
        super();
        this.date = new Date();
    }

    public Event(String title) {
        this.title = title;
        this.date = new Date();
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Event)) return false;
        if (!super.equals(o)) return false;

        Event event = (Event) o;

        if (date != null ? !date.equals(event.date) : event.date != null) return false;
        if (title != null ? !title.equals(event.title) : event.title != null) return false;

        return true;
    }

    /**
     * Overriding {@link org.kornicameister.tutorial.qubic.PersistenceObject#hashCode()} method
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
        result = 31 * result + (date != null ? date.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        sb.append("Event");
        sb.append("{title='").append(title).append('\'');
        sb.append(", date=").append(date);
        sb.append('}');
        return sb.append(" [ ").append(super.toString()).append(" ]").toString();
    }
}
