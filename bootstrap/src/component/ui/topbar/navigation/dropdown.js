import React from 'react';

export default class TopbarNavDropdown extends React.Component {
    static __dropdowns = [];

    static hideall() {
        TopbarNavDropdown.__dropdowns.forEach(o => o.hide());
    }

    constructor(props) {
        super(props);
        this.state = {
            visible: false
        };

        this.hide = this.hide.bind(this);
        this.toggle = this.toggle.bind(this);

        TopbarNavDropdown.__dropdowns.push(this);
    }

    hide() {
        this.setState({visible: false});
    }

    toggle() {
        console.log("toggle");
        if(!this.state.visible) {
            TopbarNavDropdown.hideall();
        }
        this.setState({visible: !this.state.visible});
    }
}