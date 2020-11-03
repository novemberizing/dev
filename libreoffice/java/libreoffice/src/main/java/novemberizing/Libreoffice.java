package novemberizing;

import com.sun.star.awt.Point;
import com.sun.star.beans.*;
import com.sun.star.comp.helper.BootstrapException;
import com.sun.star.frame.XStorable;
import com.sun.star.lang.WrappedTargetException;
import com.sun.star.lib.uno.helper.PropertySet;
import com.sun.star.style.ParagraphAdjust;
import com.sun.star.text.ParagraphVertAlign;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.comp.helper.Bootstrap;
import com.sun.star.frame.XComponentLoader;
import com.sun.star.lang.XComponent;
import com.sun.star.lang.XMultiComponentFactory;
import com.sun.star.container.XIndexAccess;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.awt.Size;
import com.sun.star.text.XText;
import com.sun.star.text.XTextCursor;
import com.sun.star.text.XTextRange;
import com.sun.star.view.PaperFormat;
import com.sun.star.view.XPrintable;

import com.sun.star.drawing.XDrawPage;
import com.sun.star.drawing.XShapes;
import com.sun.star.drawing.XShape;
import com.sun.star.drawing.XDrawPagesSupplier;
import com.sun.star.drawing.XDrawPages;
import com.sun.star.style.TabStop;

public class Libreoffice {

    public static class Draw {
        public static void text(XComponent component, XDrawPage page, String v) {
            XMultiServiceFactory factory = UnoRuntime.queryInterface(XMultiServiceFactory.class, component);
            XShapes xShapes = UnoRuntime.queryInterface(XShapes.class, page);
            XPrintable printable = UnoRuntime.queryInterface(XPrintable.class, component);
            System.out.println(printable);
            PropertyValue[] values = printable.getPrinter();

            for(int i = 0; i < values.length; i++) {
                PropertyValue value = values[i];
                if(value.Name.equals("PaperFormat")) {
                    value.Value = PaperFormat.USER;
                    values[i] = value;
                }
            }
            printable.setPrinter(values);
            XPropertySet propertySet = UnoRuntime.queryInterface(XPropertySet.class, page);

            try {
                propertySet.setPropertyValue("Height", (int)(630 * 26.458333333f));
                propertySet.setPropertyValue("Width", (int)(1200 * 26.458333333f));
            } catch (UnknownPropertyException | PropertyVetoException | WrappedTargetException e) {
                e.printStackTrace();
            }

            try {
                Object instance = factory.createInstance("com.sun.star.drawing.TextShape");

                XShape shape = UnoRuntime.queryInterface(XShape.class, instance);
                xShapes.add(shape);

                Point position = new Point();
                position.X = (int)(0.39f * 2540);
                position.Y = (int)(0.39f * 2540);

                // -0.39″

                shape.setPosition(position);

                Size size = new Size();
                size.Width = (int)(1200 * 26.458333333f - (0.39f * 2540) * 2);
                size.Height = (int)(630 * 26.458333333f - (0.39f * 2540) * 2);
                shape.setSize(size);

                XText text = UnoRuntime.queryInterface(XText.class, shape);

                XTextCursor cursor = text.createTextCursor();
                cursor.gotoEnd(false);
                XTextRange range = UnoRuntime.queryInterface(XTextRange.class, cursor);
                range.setString(v);
                cursor.gotoEnd(true);
                XPropertySet properties = UnoRuntime.queryInterface(XPropertySet.class, range);
                properties.setPropertyValue("CharFontName", "Noto Serif CJK JP ExtraLight");
                properties.setPropertyValue("CharFontNameAsian", "Noto Serif CJK JP ExtraLight");
                properties.setPropertyValue("CharHeightAsian", 70);
                properties.setPropertyValue("CharHeight", 70);
                properties.setPropertyValue("ParaAdjust", ParagraphAdjust.CENTER);

                Util.print(properties);

                XStorable storable = UnoRuntime.queryInterface(XStorable.class, component);

                values = new PropertyValue[2];
                // Setting the flag for overwriting
                values[0] = new PropertyValue();
                values[0].Name = "Overwrite";
                values[0].Value = Boolean.TRUE;
                // Setting the filter name
                values[1] = new PropertyValue();
                values[1].Name = "FilterName";
                values[1].Value = "draw_png_Export";

                storable.storeToURL("file:///home/novemberizing/test.png", values);
            } catch(Exception e) {
                e.printStackTrace();
            }

        }

        public static XDrawPage page(XComponent component, int index) {
            XDrawPage page = null;
            try {
                XDrawPagesSupplier supplier = UnoRuntime.queryInterface(XDrawPagesSupplier.class, component);
                XDrawPages pages = supplier.getDrawPages();
                XIndexAccess indices = UnoRuntime.queryInterface(XIndexAccess.class, pages);
                page = UnoRuntime.queryInterface(XDrawPage.class, indices.getByIndex(index));
            } catch(Exception e) {
                e.printStackTrace();
            }
            return page;
        }
    }

    public static class Util {
        public static void print(XPropertySet properties) {
            XPropertySetInfo info = properties.getPropertySetInfo();
            for(Property property : info.getProperties()) {
                try {
                    if(property.Name.startsWith("Para")) {
                        System.out.println(property.Name + " => " + properties.getPropertyValue(property.Name));
                    }
                } catch (UnknownPropertyException | WrappedTargetException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Component {
        public static final String draw = "private:factory/sdraw";

        public static XComponent open(XComponentContext context, String url) {
            XComponentLoader loader;
            XComponent component = null;

            XMultiComponentFactory factory = context.getServiceManager();

            try {
                Object desktop = factory.createInstanceWithContext("com.sun.star.frame.Desktop", context);
                loader = UnoRuntime.queryInterface(XComponentLoader.class, desktop);
                PropertyValue[] values = new PropertyValue[1];
                values[0] = new PropertyValue();
                values[0].Name = "Hidden";
                values[0].Value = false;
                component = loader.loadComponentFromURL(url, "_blank", 0, values);
            } catch(Exception e) {
                e.printStackTrace();
            }
            return component;
        }

        public static void close(XComponent component) {
            component.dispose();
        }
    }

    public static void main(String[] args) {
        System.out.println("Hello world");

        // 1. bootstrap uno and get the remote component context
        XComponentContext xContext;
        try {
            xContext = Bootstrap.bootstrap();
            // 2. open an empty text document
            XComponent component = Component.open(xContext, Component.draw);
            XDrawPage page = Draw.page(component, 0);

            // 3. drawing text
            Draw.text(component, page, "學而時習之 不亦說乎\n有朋自遠方來 不亦樂乎\n人不知而不慍 不亦君子乎");

            // 4. dispose
            // Component.close(component);
        } catch (BootstrapException e) {
            e.printStackTrace();
        }
    }
}
