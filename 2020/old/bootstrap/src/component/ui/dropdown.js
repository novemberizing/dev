import React from 'react';

export default class Dropdown extends React.Component {
    static __dropdowns = [];

    static hideall() {
        Dropdown.__dropdowns.forEach(o => o.hide());
    }

    constructor(props) {
        super(props);
        this.state = {
            visible: false
        };

        this.hide = this.hide.bind(this);
        this.toggle = this.toggle.bind(this);

        Dropdown.__dropdowns.push(this);
    }

    hide() {
        this.setState({visible: false});
    }

    toggle() {
        if(!this.state.visible) {
            Dropdown.hideall();
        }
        this.setState({visible: !this.state.visible});
    }
}