// DOM Elements
const navbar = document.getElementById('navbar');
const progressBar = document.getElementById('progress-bar');
const backToTopBtn = document.getElementById('back-to-top');
const accordionHeaders = document.querySelectorAll('.accordion-header');


// 1. Scroll Events
window.addEventListener('scroll', () => {
    // Scroll Progress Bar
    const scrollPercent = (window.scrollY / (document.documentElement.scrollHeight - window.innerHeight)) * 100;
    progressBar.style.width = scrollPercent + '%';

    // Navbar shadow on scroll
    if (window.scrollY > 50) {
        navbar.classList.add('scrolled');
    } else {
        navbar.classList.remove('scrolled');
    }

    // Back to top button visibility
    if (window.scrollY > 500) {
        backToTopBtn.classList.add('visible');
    } else {
        backToTopBtn.classList.remove('visible');
    }
});

// 2. Back to Top Click
backToTopBtn.addEventListener('click', () => {
    window.scrollTo({
        top: 0,
        behavior: 'smooth'
    });
});

// 3. FAQ Accordion Toggle
accordionHeaders.forEach(header => {
    header.addEventListener('click', () => {
        const item = header.parentElement;

        // Close other items (optional)
        document.querySelectorAll('.accordion-item').forEach(otherItem => {
            if (otherItem !== item) {
                otherItem.classList.remove('active');
            }
        });

        // Toggle current item
        item.classList.toggle('active');
    });
});

// 4. Reveal Animations (Intersection Observer)
const revealOptions = {
    threshold: 0.1,
    rootMargin: "0px 0px -100px 0px"
};

const revealObserver = new IntersectionObserver((entries, observer) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('revealed');
            observer.unobserve(entry.target);
        }
    });
}, revealOptions);

const revealElements = document.querySelectorAll('.reveal-up, .reveal-left, .reveal-right');
revealElements.forEach(el => revealObserver.observe(el));

// 5. Scroll Spy (Active Navbar Links)
const sections = document.querySelectorAll('.scroll-spy-section, #hero, #components, #connections');
const navLinks = document.querySelectorAll('.nav-links a');

const scrollSpyOptions = {
    threshold: 0.5,
    rootMargin: "-70px 0px 0px 0px"
};

const scrollSpyObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const id = entry.target.getAttribute('id');
            navLinks.forEach(link => {
                link.classList.remove('active');
                if (link.getAttribute('href') === `#${id}`) {
                    link.classList.add('active');
                }
            });
        }
    });
}, scrollSpyOptions);

sections.forEach(section => scrollSpyObserver.observe(section));

// 6. Connections Section Interactivity (Wire + Pin Dot Highlight)
const wireRows = document.querySelectorAll('.wire-row');
const svgWires = document.querySelectorAll('.svg-wire');

// Map each wire ID to its two pin dot element IDs
const wirePinMap = {
    vcc: ['dot-mpu-vcc', 'dot-esp-vcc'],
    gnd: ['dot-mpu-gnd', 'dot-esp-gnd'],
    sda: ['dot-mpu-sda', 'dot-esp-sda'],
    scl: ['dot-mpu-scl', 'dot-esp-scl'],
};

function clearHighlights() {
    svgWires.forEach(w => w.classList.remove('active'));
    Object.values(wirePinMap).flat().forEach(id => {
        const el = document.getElementById(id);
        if (el) el.classList.remove('svg-dot-active');
    });
}

wireRows.forEach(row => {
    row.addEventListener('mouseenter', () => {
        const wireId = row.getAttribute('data-wire');
        if (!wireId) return;
        clearHighlights();

        // Highlight wire
        const wire = document.getElementById(`wire-${wireId}`);
        if (wire) wire.classList.add('active');

        // Highlight both pin dots
        const dots = wirePinMap[wireId] || [];
        dots.forEach(dotId => {
            const dot = document.getElementById(dotId);
            if (dot) dot.classList.add('svg-dot-active');
        });
    });

    row.addEventListener('mouseleave', clearHighlights);
});


// 7. Parallax Effect on Hero
window.addEventListener('scroll', () => {
    const heroContent = document.querySelector('.hero-content');
    const scrolled = window.scrollY;
    if (scrolled < window.innerHeight) {
        heroContent.style.transform = `translateY(${scrolled * 0.4}px)`;
        heroContent.style.opacity = 1 - (scrolled / (window.innerHeight * 1.5));
    }
});



