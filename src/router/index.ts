import { createRouter, createWebHistory, createWebHashHistory } from 'vue-router'

const router = createRouter({
  // history: createWebHistory(import.meta.env.BASE_URL),
  history: createWebHashHistory(),
  routes: [
    {
      path: '/',
      name: 'home',
      component: () => import('../views/HomeView.vue'),
    },
    {
      path: '/about',
      name: 'about',
      // route level code-splitting
      // this generates a separate chunk (About.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import('../components/display/AboutView.vue'),
    },
    {
      path: '/pms',
      name: 'pms',
      component: () => import('../components/display/PmsView.vue'),
    },
    {
      path: '/dcs-chain',
      name: 'dcs-chain',
      component: () => import('../components/display/DCSView.vue'),
    },
    {
      path: '/contact',
      name: 'contact',
      component: () => import('../components/display/ContactView.vue'),
    },
    {
      path: '/MCU',
      name: 'MCU',
      component: () => import('../components/display/McuView.vue'),
    },
    {
      path: '/sokoban',
      name: '/sokoban',
      component: () => import('../components/display/SokobanView.vue'),
    },
    {
      path: '/drinkSeller',
      name: '/drinkSeller',
      component: () => import('../components/display/DrinkSellerView.vue'),
    },
    {
      path: '/os',
      name: '/os',
      component: () => import('../components/display/OsView.vue'),
    },
    {
      path: '/other',
      name: 'other',
      component: () => import('../components/display/OtherView.vue'),
    },
    {
      path: '/abstractFactory',
      name: 'abstractFactory',
      component: () => import('../components/display/AbstractFactory.vue'),
    }
  ],
})

export default router
