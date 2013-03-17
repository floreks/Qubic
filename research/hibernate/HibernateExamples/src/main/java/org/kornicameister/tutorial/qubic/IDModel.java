package org.kornicameister.tutorial.qubic;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;

/**
 * <i>
 * This class shows how to use the advantages of classical
 * class inheritance with Hibernate. There is often a strong
 * need to extract some fields to upper level class for support
 * their usability in the inheritance branch.
 * </i>
 * <p>
 * The class below has some important parts to talk over.
 * <ul>
 * <li>
 * <b>abstract</b> - {@link IDModel} class is declared
 * as abstract. This, although not strictly required or AFAIK not
 * recommended, is the approach I prefer. It emphasises the
 * purpose of the class - being the base for entire family
 * of persistence entities for Hibernate.
 * </li>
 * <li>
 * {@link MappedSuperclass} - annotation used by Hibernate
 * to recognize that the class is not meant to have equivalent
 * in the database. All it does is encapsulating some
 * fields for extending classes.
 * </li>
 * <li>
 * {@link IDModel#id} - single field to share among
 * all extending classes
 * </li>
 * <li>
 * {@link IDModel#hashCode()} -
 * this method is vital for hibernate. I may be wrong at the moment, but I
 * strongly believe that this is the way which Hibernate uses to
 * distinguish one object from another and therefore one row from another
 * in the database. Instead of runtime checkup for the table's primary key
 * being equal or not, the standard Java approach is used to establish
 * whether or not one object can be considered as equal to another.
 * </li>
 * </ul>
 * </p>
 * <p/>
 * <p style="font-weight:bold">
 * Note 1:
 * <i>
 * Variables declared in abstract base will be used in
 * each extending model and therefore available under the same
 * name in the databases' tables (if not defined otherwise).
 * For example, here we have {@link IDModel#id}.
 * </i>
 * </p>
 * <p style="font-weight:bold">
 * Note 2:
 * <i>
 * Every non static non transient property (field or method depending
 * on the access type) of an entity is considered persistent,
 * unless you annotate it as @Transient. Not having an annotation
 * for your property is equivalent to the appropriate @Basic annotation.
 * </i>
 * </p>
 *
 * @author kornicameister
 * @version 0.1
 * @since 2013-01-27
 */
@MappedSuperclass
public class IDModel extends AbstractModel {
    @Transient
    private static final long serialVersionUID = 8641451013192983600L;

    /**
     * Primary key for the model and therefore for each
     * table in database. What is important that if
     * The field lacks from {@link Column} annotation
     * then, apart from other properties not important at the moment,
     * the field name will be used in all corresponding tables.
     * Here it stands for <b>primaryKey</b>.
     *
     * <p style="font-weight:bold">Important things to remember</p>
     * <p>
     *    As you see below field that is described as {@link Id} also
     *    has some other important annotations. Here is the quick desc:
     *    <ul>
     *        <li><b>{@link GeneratedValue}</b> - one of its option is strategy, here
     *        we call for {@link GenerationType#IDENTITY} therefore pointing for
     *        the field to be unique identifier</li>
     *        <li><b>{@link GenericGenerator}</b> - is useful utility that automatically
     *        increments this field's value by one for each new record</li>
     *    </ul>
     * </p>
     */
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @GenericGenerator(name = "increment", strategy = "increment")
    @Column(name = "primaryKey")
    private Long id = null;

    public IDModel() {
        super();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof IDModel)) return false;
        if (!super.equals(o)) return false;

        IDModel idModel = (IDModel) o;

        return !(id != null ? !id.equals(idModel.id) : idModel.id != null);
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (id != null ? id.hashCode() : 0);
        return result;
    }
}
