import 'bootstrap/dist/css/bootstrap.css';
import 'bootstrap/dist/js/bootstrap.bundle';
// import './bootstrap.css';

import '@fortawesome/fontawesome-free/css/all.css';
import React from 'react';
import ReactDOM from 'react-dom';

import { library } from '@fortawesome/fontawesome-svg-core';
import { fab } from '@fortawesome/free-brands-svg-icons';
import { fas } from '@fortawesome/free-solid-svg-icons';

import Header from './bootstrap/components/header';
import Blockquote from './bootstrap/components/blockquote';
import Paragraph from './bootstrap/components/paragraph';
import Footer from './bootstrap/components/footer';
import Button from './bootstrap/components/button';
import Dropdown from './bootstrap/components/dropdown';
import RadioBtn from './bootstrap/components/button/radio';
import CheckboxBtn from './bootstrap/components/button/checkbox';
import ButtonGroup from './bootstrap/components/button/group';
import ButtonBar from './bootstrap/components/button/bar';
import Toggle from './bootstrap/components/button/toggle';
import Input from './bootstrap/components/input';
import InputText from './bootstrap/components/input/text';
import InputGroup from './bootstrap/components/input/group';
import Hyperlink from './bootstrap/components/hyperlink';
import Accordion from './bootstrap/components/accordion';
import AccordionItem from './bootstrap/components/accordion/item';
import Alert from './bootstrap/components/alert';
import Badge from './bootstrap/components/badge';
import Breadcrumb from './bootstrap/components/breadcrumb';
import BreadcrumbItem from './bootstrap/components/breadcrumb/item';
import ListItem from './bootstrap/components/list/item';
import Divider from './bootstrap/components/divider';
import Brand from './bootstrap/components/brand';
import Collapse from './bootstrap/components/collapse';
import NavigationBar from './bootstrap/components/navigation/bar';
import Navigation from './bootstrap/components/navigation';
import Tab from './bootstrap/components/tab';
import Panel from './bootstrap/components/panel';
import Form from './bootstrap/components/form';
import Text from './bootstrap/components/text';
import Card from './bootstrap/components/card';
import Body from './bootstrap/components/body';
import Title from './bootstrap/components/title';
import Subtitle from './bootstrap/components/subtitle';
import List from './bootstrap/components/list';
import CardGroup from './bootstrap/components/card/group';
import Carousel from './bootstrap/components/carousel';
import CarouselInner from './bootstrap/components/carousel/inner';
import CarouselItem from './bootstrap/components/carousel/item';
import CarouselIndicator from './bootstrap/components/carousel/indicator';
import Modal from './bootstrap/components/modal';
import Content from './bootstrap/components/content';
import Pagination from './bootstrap/components/pagination';
import Popover from './bootstrap/components/popover';
import Progress from './bootstrap/components/progress';
import ProgressBar from './bootstrap/components/progress/bar';
import ScrollSpy from './bootstrap/components/scrollspy';
import Spinner from './bootstrap/components/spinner';
import Toast from './bootstrap/components/toast';
import Tooltip from './bootstrap/components/tooltip';
import Label from './bootstrap/components/label';
import Select from './bootstrap/components/select';
import Check from './bootstrap/components/input/check';
import Radio from './bootstrap/components/input/radio';
import Range from './bootstrap/components/input/range';
import Floating from './bootstrap/components/input/floating';

import Context from './bootstrap/context';
import Contextual from './bootstrap/contextual';
import Breakpoint from './bootstrap/breakpoint';

import ExampleView from './bootstrap/example';
import ExampleAccordionView from './bootstrap/example/accordion';
import ExampleAlertView from './bootstrap/example/alert';
import ExampleBadgeView from './bootstrap/example/badge';
import ExampleBreadcrumbView from './bootstrap/example/breadcrumb';
import ExampleButtonView from './bootstrap/example/button';
import ExampleCardView from './bootstrap/example/card';
import ExampleButtonGroupView from './bootstrap/example/buttongroup';
import ExampleCarouselView from './bootstrap/example/carousel';
import ExampleCollapseView from './bootstrap/example/collapse';
import ExampleDropdownView from './bootstrap/example/dropdown';
import ExampleNavigationView from './bootstrap/example/navigation';
import ExampleNavigationBarView from './bootstrap/example/navigationbar';
import ExampleListGroupView from './bootstrap/example/listgroup';
import ExampleModalView from './bootstrap/example/modal';
import ExamplePaginationView from './bootstrap/example/pagination';
import ExamplePopoverView from './bootstrap/example/popover';
import ExampleProgressView from './bootstrap/example/progress';
import ExampleScrollSpyView from './bootstrap/example/scrollspy';
import ExampleSpinnerView from './bootstrap/example/spinner';
import ExampleToastView from './bootstrap/example/toast';
import ExampleTooltipView from './bootstrap/example/tooltip';
import ExampleFormView from './bootstrap/example/form';
import ExampleFormControlView from './bootstrap/example/form/control';
import ExampleFormSelectView from './bootstrap/example/form/select';
import ExampleFormCheckView from './bootstrap/example/form/check';
import ExampleFormRangeView from './bootstrap/example/form/range';
import ExampleFormGroupView from './bootstrap/example/form/group';

import ExampleFormFloatingView from './bootstrap/example/form/floating';
import ExampleFormLayoutView from './bootstrap/example/form/layout';


library.add(fab);
library.add(fas);

class Root extends React.Component {
    
    render() {
        return (
            <div className="container-fluid">
                <ExampleFormLayoutView />
                <ExampleFormFloatingView />
                <ExampleFormGroupView />
                <ExampleFormRangeView />
                <ExampleFormCheckView />
                <ExampleFormSelectView />
                <ExampleFormControlView />
                <ExampleFormView />
                <ExampleTooltipView />
                <ExampleToastView />
                <ExampleSpinnerView />
                <ExampleScrollSpyView />
                <ExampleProgressView />
                <ExamplePopoverView />
                <ExamplePaginationView />
                <ExampleModalView />
                <ExampleListGroupView />
                <ExampleNavigationBarView />
                <ExampleNavigationView />
                <ExampleDropdownView />
                <ExampleCollapseView />
                <ExampleCarouselView />
                <ExampleButtonGroupView />
                <ExampleCardView />
                <ExampleButtonView />
                <ExampleBreadcrumbView />
                <ExampleBadgeView />
                <ExampleAccordionView />
                <ExampleAlertView />
                <ExampleView />
            </div>
        );
    }
}

ReactDOM.render(<Root />, document.getElementById('root'));
