
import React from 'react';

import Context from '../../context';

import Strings from '../../../util/strings';
import Breakpoint from '../../breakpoint';
import Contextual from '../../contextual';

export default class NavigationBar extends Context {
    static get sm(){ return Breakpoint.sm; }
    static get md(){ return Breakpoint.md; }
    static get lg(){ return Breakpoint.lg; }
    static get xl(){ return Breakpoint.xl; }
    static get xxl(){ return Breakpoint.xxl; }

    static expand(prefix, type, suffix = undefined, separator = '-') {
        switch(type) {
            case NavigationBar.sm:  return Strings.join([prefix, type, suffix], separator);
            case NavigationBar.md:  return Strings.join([prefix, type, suffix], separator);
            case NavigationBar.lg:  return Strings.join([prefix, type, suffix], separator);
            case NavigationBar.xl:  return Strings.join([prefix, type, suffix], separator);
            case NavigationBar.xxl: return Strings.join([prefix, type, suffix], separator);
        }
        return undefined;
    }

    constructor(props) {
        super(props);
    }

    render() {
        const {
            className,
            children,
            expand,
            contextual,
            background,
            ...additional
        } = this.props;

        const classNames = Strings.join([
            className,
            "navbar",
            NavigationBar.expand('navbar-expand', expand),
            Contextual.name('navbar', contextual),
            (!additional.style || !additional.style.backgroundColor) && Contextual.name('bg', background || contextual)
        ]);

        const props = Object.assign(additional,
            {}
        );

        const context = {
            type: Context.push(this.context.type, "navbar")
        };

        return (
            <Context.Provider value={context}>
                <nav className={classNames} {...props}>
                    <div className="container-fluid">
                        {children}
                    </div>
                </nav>
            </Context.Provider>
        );
    }
}