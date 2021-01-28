/**
 * 
 */
import React, { Component } from 'react';

import Carousel from '../components/carousel';
import CarouselIndicator from '../components/carousel/indicator';
import CarouselInner from '../components/carousel/inner';
import CarouselItem from '../components/carousel/item';
import ListItem from '../components/list/item';
import Header from '../components/header';
import Paragraph from '../components/paragraph';
import Hyperlink from '../components/hyperlink';
import Context from '../context';

import sample from '../../sample.jpg';

export default class ExampleCarouselView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <Context.Provider value={{type:[]}}>
                <div className="container-fluid">
                    {/** CAROUSEL: INTERVAL */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls7" onSlide={event=>console.log('carousel', event)} onSlid={event=>console.log('carousel', event)}>
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} interval="10000" >
                                    <Header size={5}>First slide label</Header>
                                    <Paragraph>Nulla vitae elit libero, a pharetra augue mollis interdum.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}}  interval="100" >
                                    <Header size={5}>Second  slide label</Header>
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Third  slide label</Header>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur.</Paragraph>
                                </CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls7" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls7" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL: INTERVAL */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls7" dark>
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls7" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} interval="10000" >
                                    <Header size={5}>First slide label</Header>
                                    <Paragraph>Nulla vitae elit libero, a pharetra augue mollis interdum.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}}  interval="100" >
                                    <Header size={5}>Second  slide label</Header>
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Third  slide label</Header>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur.</Paragraph>
                                </CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls7" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls7" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL: INTERVAL */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls5">
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls5" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls5" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls5" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} interval="10000" >
                                    <Header size={5}>First slide label</Header>
                                    <Paragraph>Nulla vitae elit libero, a pharetra augue mollis interdum.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}}  interval="100" >
                                    <Header size={5}>Second  slide label</Header>
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Third  slide label</Header>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur.</Paragraph>
                                </CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls5" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls5" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL: INDICATOR + CAPTION*/}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls4" fade>
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>First slide label</Header>
                                    <Paragraph>Nulla vitae elit libero, a pharetra augue mollis interdum.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Second  slide label</Header>
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Third  slide label</Header>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur.</Paragraph>
                                </CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls4" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls4" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL: INDICATOR + CAPTION*/}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls4">
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls4" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>First slide label</Header>
                                    <Paragraph>Nulla vitae elit libero, a pharetra augue mollis interdum.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Second  slide label</Header>
                                    <Paragraph>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</Paragraph>
                                </CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} >
                                    <Header size={5}>Third  slide label</Header>
                                    <Paragraph>Praesent commodo cursus magna, vel scelerisque nisl consectetur.</Paragraph>
                                </CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls4" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls4" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL: INDICATOR */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls3">
                            <CarouselIndicator>
                                <ListItem data-bs-target="#carouselExampleControls3" data-bs-slide-to="0" active></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls3" data-bs-slide-to="1"></ListItem>
                                <ListItem data-bs-target="#carouselExampleControls3" data-bs-slide-to="2"></ListItem>
                            </CarouselIndicator>
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} ></CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} ></CarouselItem>
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} ></CarouselItem>
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls3" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls3" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls2">
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                            </CarouselInner>
                            <Hyperlink role="button" className="carousel-control-prev" href="#carouselExampleControls2" data-bs-slide="prev">
                                <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Previous</span>
                            </Hyperlink>
                            <Hyperlink role="button" className="carousel-control-next" href="#carouselExampleControls2" data-bs-slide="next">
                                <span className="carousel-control-next-icon" aria-hidden="true"></span>
                                <span className="visually-hidden">Next</span>
                            </Hyperlink>
                        </Carousel>
                    </div>
                    {/** CAROUSEL */}
                    <div style={{padding: '5px'}}>
                        <Carousel id="carouselExampleControls">
                            <CarouselInner>
                                <CarouselItem active src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                                <CarouselItem src={sample} className="d-block w-100" alt="alt" style={{height: '400px'}} />
                            </CarouselInner>
                        </Carousel>
                    </div>
                </div>
            </Context.Provider>
        );
    }
}