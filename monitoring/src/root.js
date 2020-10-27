import React from 'react';
import Sidebar from './sidebar';
import Content from './content';
import NavigationBar from './navigation-bar';

export default class Root extends React.Component {
    render() {
        return (<div>
                    <NavigationBar>
                        <NavigationBar.Brand />
                    </NavigationBar>
                    <Content />
                </div>);
    }
}
