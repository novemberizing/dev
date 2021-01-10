import React from 'react';
import Sidebar from '../sidebar';

import TopbarBtn from './button';
import TopbarNav from './navigation';
import TopbarSearch from './search';

export default class Topbar extends React.Component {

    static __singleton = null;

    constructor(props) {
        super(props);

        if(Topbar.__singleton) {
            throw new Error();
        }

        Topbar.__singleton = this;
    }

    render() {
        return (
            <nav className="navbar navbar-expand navbar-light bg-white topbar mb-4 static-top shadow">
                <TopbarBtn icon={["fas", "bars"]} onClick={Sidebar.toggle} />
                <TopbarSearch />
                <TopbarNav />

                
            </nav>
        );
    }
}

Topbar.Btn = TopbarBtn;
Topbar.Search = TopbarSearch;
Topbar.Nav = TopbarNav;
